#include "timer.h"
#include <pthread.h>

#include <sys/time.h>
#include <stdlib.h>

#include "lib/error.h"
#include "cb_lock.h"

typedef struct {
    uint32_t dt;
    uint32_t t0;
    bool run;
    bool canceled;
    bool oneShot;
} Settings;

typedef struct {
    pthread_t thread;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} Thread;

typedef struct {
    timer_Callback* callback;
    Settings settings;
    Thread thread;
} Handle;

#define LOCK if (pthread_mutex_lock(&handle->thread.mutex) != 0) { errorExit("mutex_lock"); }
#define UNLOCK if (pthread_mutex_unlock(&handle->thread.mutex) != 0) { errorExit("mutex unlock"); }
#define SIGNAL if (pthread_cond_signal(&handle->thread.cond) != 0) { errorExit("cond_signal"); }
#define HANDLE Handle* handle = (Handle*)h;

static void* run(void* h);
static uint32_t getNow();

void* timer_wire(timer_Callback* callback)
{
    Handle* handle = malloc(sizeof(Handle));
    handle->callback = callback;

    // predefine settings
    handle->settings.dt = 0;
    handle->settings.t0 = 0;
    handle->settings.run = FALSE;
    handle->settings.canceled = FALSE;
    handle->settings.oneShot = FALSE;
    
    // init new timer thread
    pthread_cond_init(&handle->thread.cond, NULL);
    pthread_mutex_init(&handle->thread.mutex, NULL);
    pthread_create(&handle->thread.thread, NULL, run, handle);

    // sync with new thread
    LOCK;
    pthread_cond_wait(&handle->thread.cond, &handle->thread.mutex);
    UNLOCK;

    return handle;
}

void timer_startPeriodic(void* handle, uint32_t dt)
{
    timer_startPeriodicAt(handle, timer_getNow(handle), dt);
}

void timer_startOneShot(void* handle, uint32_t dt)
{
    timer_startOneShotAt(handle, timer_getNow(handle), dt);
}

void timer_stop(void* h)
{
    HANDLE;
    LOCK;
    handle->settings.run = FALSE;
    handle->settings.oneShot = FALSE;
    handle->settings.canceled = TRUE;
    SIGNAL;
    UNLOCK;
}

bool timer_isRunning(void* h)
{
    HANDLE;
    bool res;
    LOCK;
    res = handle->settings.run == TRUE;
    UNLOCK;
    return res;
}

bool timer_isOneShot(void* h)
{
    HANDLE;
    bool res;
    LOCK;
    res = handle->settings.oneShot;
    UNLOCK;
    return res;
}

void timer_startPeriodicAt(void* h, uint32_t t0, uint32_t dt)
{
    HANDLE;
    LOCK;
    handle->settings.t0 = t0;
    handle->settings.dt = dt;
    handle->settings.oneShot = FALSE;
    handle->settings.run = TRUE;
    handle->settings.canceled = TRUE;
    SIGNAL;
    UNLOCK;
}

void timer_startOneShotAt(void* h, uint32_t t0, uint32_t dt)
{
    HANDLE;
    LOCK;
    handle->settings.t0 = t0;
    handle->settings.dt = dt;
    handle->settings.oneShot = TRUE;
    handle->settings.run = TRUE;
    handle->settings.canceled = TRUE;
    SIGNAL;
    UNLOCK;
}

uint32_t timer_getNow(void* h)
{
	(void)h;
    return getNow();
}

uint32_t timer_gett0(void* h)
{
    HANDLE;
    uint32_t res;
    LOCK;
    res = handle->settings.t0;
    UNLOCK;
    return res;
}

uint32_t timer_getdt(void* h)
{
    HANDLE;
    uint32_t res;
    LOCK;
    res = handle->settings.dt;
    UNLOCK;
    return res;
}

static uint32_t getNow()
{
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    if (res == -1) {
        errorExit("gettimeofday");
    }
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static struct timespec getAbsTime(Handle* handle)
{
    struct timespec abstime;
    uint64_t then = getNow() + handle->settings.t0;
    abstime.tv_sec = then / 1000;
    abstime.tv_nsec = (then % 1000) * 1000 * 1000;
    return abstime;
}

static void* run(void* h)
{
    HANDLE;
    LOCK;
    SIGNAL;
    while(1) {
        if (handle->settings.run) {
            struct timespec abstime = getAbsTime(handle);
            pthread_cond_timedwait(&handle->thread.cond, &handle->thread.mutex, &abstime);    
        } else {
            pthread_cond_wait(&handle->thread.cond, &handle->thread.mutex);
        }

        if (handle->settings.canceled) {
            handle->settings.canceled = FALSE;
        } else {
            cb_lock_acquire();
            handle->settings.t0 = getNow();
            handle->callback->fired(handle);
            cb_lock_release();

            if (handle->settings.oneShot) {
                handle->settings.oneShot = FALSE;
                handle->settings.run = FALSE;
            }
        }
    }
    UNLOCK; 
    return NULL;
}
