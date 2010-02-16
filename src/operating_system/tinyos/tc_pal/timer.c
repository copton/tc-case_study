#include "Timer.h"
#include "raw/Timer.h"
#include <assert.h>

static void* timer_handle;

uint64_t timers[TC_NUMBEROF_THREADS];

static tc_tid_t findThread()
{
    uint32_t now = timer_getNow(timer_handle);
    int dt;
    tc_tid_t i;
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
    tc_tid = findThread(handle);
    unsigned idx = tc_map_timer_sleep(tc_tid);
    tc_state_timer_sleep[idx].tc_continuation();
}

static timer_Callback callback = {&fired};

void timer_init()
{
    timer_handle = timer_wire(&callback);
}

void tc_pal_timer_sleep(uint64_t until)
{
    assert (timers[tc_tid] == 0);
    timers[tc_tid] = until;
    timer_startOneShot(timer_handle, until - timer_getNow(timer_handle));
}

uint64_t tc_pal_timer_getNow()
{
	return timer_getNow(timer_handle);
}
