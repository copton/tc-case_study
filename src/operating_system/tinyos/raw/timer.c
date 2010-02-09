#include "time_types.h"
#include "Timer.h"

typedef timer_Callback Callback;

typedef struct {
    RelTime dt;
    RelTime t0;
    bool run;
    bool newSettings;
    bool oneShot;
} Shared;

#include "component.h"

#include <time.h>

static AbsTime getNow();
static void* run(void* handle);

void* timer_wire(timer_Callback* callback)
{
	Handle* handle = malloc(sizeof(Handle));
	handle->callback = callback;

    handle->shared.dt = rt_create(0);
	handle->shared.t0 = rt_create(0);
	handle->shared.run = FALSE;
	handle->shared.newSettings = FALSE;
	handle->shared.oneShot = FALSE;

    setupThread(handle);

    return handle;
}

void timer_startPeriodic(void* h, uint32_t dt)
{
	DEBUGOUT("timer_startPeriodic(%p, %u)\n", h, dt);
    timer_startPeriodicAt(h, timer_getNow(h), dt);
}

void timer_startOneShot(void* h, uint32_t dt)
{
    timer_startOneShotAt(h, timer_getNow(h), dt);
}

void timer_stop(void* h)
{
    HANDLE;
    LOCK;
    handle->shared.run = FALSE;
    handle->shared.oneShot = FALSE;
    handle->shared.newSettings = TRUE;
    SIGNAL;
    UNLOCK;
}

bool timer_isRunning(void* h)
{
    HANDLE;
    bool res;
    LOCK;
    res = handle->shared.run == TRUE;
    UNLOCK;
    return res;
}

bool timer_isOneShot(void* h)
{
    HANDLE;
    bool res;
    LOCK;
    res = handle->shared.oneShot;
    UNLOCK;
    return res;
}

void timer_startPeriodicAt(void* h, uint32_t t0, uint32_t dt)
{
	DEBUGOUT("timer_startPeriodicAt(%p, %u, %u)\n", h, t0, dt);
    HANDLE;
    LOCK;
    handle->shared.t0 = rt_create(t0);
    handle->shared.dt = rt_create(dt);
    handle->shared.oneShot = FALSE;
    handle->shared.run = TRUE;
    handle->shared.newSettings = TRUE;
    SIGNAL;
    UNLOCK;
}

void timer_startOneShotAt(void* h, uint32_t t0, uint32_t dt)
{
    HANDLE;
    LOCK;
    handle->shared.t0 = rt_create(t0);
    handle->shared.dt = rt_create(dt);
    handle->shared.oneShot = TRUE;
    handle->shared.run = TRUE;
    handle->shared.newSettings = TRUE;
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
    res = rt_unpack(handle->shared.t0);
    UNLOCK;
    return res;
}

uint32_t timer_getdt(void* h)
{
    HANDLE;
    uint32_t res;
    LOCK;
    res = rt_unpack(handle->shared.dt);
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
	if (rt_le(handle->shared.t0, now_rel)) {
		then = at_plus(at_plus(frame, handle->shared.t0), handle->shared.dt);
	} else {
		AbsTime prevFrame = at_prevFrame(frame);
		then = at_plus(at_plus(prevFrame, handle->shared.t0), handle->shared.dt);
	}
	struct timespec res;
    res.tv_sec = at_unpack(then) / 1000;
    res.tv_nsec = (at_unpack(then) % 1000) * 1000 * 1000;
    return res;
}

static void* run(void* h)
{
	DEBUGOUT("timer::run(%p)\n", h);
    HANDLE;
    LOCK;
    SIGNAL;
    while(1) {
        if (handle->shared.run) {
            struct timespec abstime = toTimeSpec(handle);
            pthread_cond_timedwait(&handle->thread.cond, &handle->thread.mutex, &abstime);    
        } else {
            pthread_cond_wait(&handle->thread.cond, &handle->thread.mutex);
        }

        if (handle->shared.newSettings) {
            handle->shared.newSettings = FALSE;
        } else {
            cb_lock_acquire();
            handle->shared.t0 = rt_plus(handle->shared.t0, handle->shared.dt);
            handle->callback->fired(handle);
            cb_lock_release();

            if (handle->shared.oneShot) {
                handle->shared.oneShot = FALSE;
                handle->shared.run = FALSE;
            }
        }
    }
    UNLOCK; 
    return NULL;
}