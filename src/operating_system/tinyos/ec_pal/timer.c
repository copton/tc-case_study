#include "Timer.h"
#include "raw/Timer.h"
#include <assert.h>
#include "timer_init.h"

static void* timer_handle;

uint64_t timers[TC_NUMBEROF_THREADS];

static ec_tid_t findThread()
{
    uint32_t now = timer_getNow(timer_handle);
    int dt;
    ec_tid_t i;
    for (dt=0; ; dt++) {
        for(i=0; i<TC_NUMBEROF_THREADS; i++) {
            if (timers[i] == now - dt) {
                return i; 
            }
        }
    }
}

static void fired(void* handle)
{
    ec_tid = findThread(handle);
    unsigned idx = ec_map_timer_sleep(ec_tid);
    ec_state_timer_sleep[idx].ec_continuation();
}

static timer_Callback callback = {&fired};

void timer_init()
{
    timer_handle = timer_wire(&callback);
}

void ec_pal_timer_sleep(uint64_t until)
{
    assert (timers[ec_tid] == 0);
    timers[ec_tid] = until;
    timer_startOneShot(timer_handle, until - timer_getNow(timer_handle));
}

uint64_t ec_pal_timer_getNow()
{
	return timer_getNow(timer_handle);
}
