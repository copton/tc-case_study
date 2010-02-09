#include "timer.h"

#include <time.h>
#include <pthread.h>

#include <stdlib.h>

#include "infra/error.h"
#include "infra/debug.h"
#include "cb_lock.h"

#include "time_types.h"

typedef struct {
    RelTime dt;
    RelTime t0;
    bool run;
    bool newSettings;
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
static AbsTime getNow();

void* timer_wire(timer_Callback* callback)
{
    Handle* handle = malloc(sizeof(Handle));
    handle->callback = callback;

    // predefine settings
    handle->settings.dt = rt_create(0);
    handle->settings.t0 = rt_create(0);
    handle->settings.run = FALSE;
    handle->settings.newSettings = FALSE;
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
    handle->settings.newSettings = TRUE;
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
    handle->settings.t0 = rt_create(t0);
    handle->settings.dt = rt_create(dt);
    handle->settings.oneShot = FALSE;
    handle->settings.run = TRUE;
    handle->settings.newSettings = TRUE;
    SIGNAL;
    UNLOCK;
}

void timer_startOneShotAt(void* h, uint32_t t0, uint32_t dt)
{
    HANDLE;
    LOCK;
    handle->settings.t0 = rt_create(t0);
    handle->settings.dt = rt_create(dt);
    handle->settings.oneShot = TRUE;
    handle->settings.run = TRUE;
    handle->settings.newSettings = TRUE;
    SIGNAL;
    UNLOCK;
}

uint32_t timer_getNow(void* h)
{
	(void)h;
    return rt_unpack(at_to_rt(getNow()));
}

uint32_t timer_gett0(void* h)
{
    HANDLE;
    uint32_t res;
    LOCK;
    res = rt_unpack(handle->settings.t0);
    UNLOCK;
    return res;
}

uint32_t timer_getdt(void* h)
{
    HANDLE;
    uint32_t res;
    LOCK;
    res = rt_unpack(handle->settings.dt);
    UNLOCK;
    return res;
}

static AbsTime getNow()
{
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    if (res == -1) {
        errorExit("gettimeofday");
    }
	return at_create(tv);
}

static struct timespec toTimeSpec(Handle* handle)
{
	AbsTime now_abs = getNow();	
	RelTime now_rel = at_to_rt(now_abs);
	AbsTime frame = at_getFrame(now_abs);
	AbsTime then;
	if (rt_le(handle->settings.t0, now_rel)) {
		then = at_plus(at_plus(frame, handle->settings.t0), handle->settings.dt);
	} else {
		AbsTime prevFrame = at_prevFrame(frame);
		then = at_plus(at_plus(prevFrame, handle->settings.t0), handle->settings.dt);
	}
	struct timespec res;
    res.tv_sec = at_unpack(then) / 1000;
    res.tv_nsec = (at_unpack(then) % 1000) * 1000 * 1000;
    return res;
}

static void* run(void* h)
{
    HANDLE;
    LOCK;
    SIGNAL;
    while(1) {
        if (handle->settings.run) {
            struct timespec abstime = toTimeSpec(handle);
            pthread_cond_timedwait(&handle->thread.cond, &handle->thread.mutex, &abstime);    
        } else {
            pthread_cond_wait(&handle->thread.cond, &handle->thread.mutex);
        }

        if (handle->settings.newSettings) {
            handle->settings.newSettings = FALSE;
        } else {
            cb_lock_acquire();
            handle->settings.t0 = rt_plus(handle->settings.t0, handle->settings.dt);
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
