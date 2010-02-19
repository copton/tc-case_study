#include "Timer.h"
#include "raw/Timer.h"
#include "timer_init.h"
#include "infra/debug.h"

#include "component.h"

static void fired(void* handle)
{
	DEBUGOUT("%d: ec_pal_timer_sleep()", ec_tid());
    ec_set_tid(findThread(handle));
    unsigned idx = ec_map_timer_sleep(ec_tid());
	DEBUGOUT("%d: ec_pal_timer_sleep() returns", ec_tid());
    ec_state_timer_sleep[idx].ec_continuation();
}

static timer_Callback callback = {&fired};

void timer_init()
{
	int i;
	for (i=0; i < ec_nthreads_timer_sleep(); i++) {
		ec_state_timer_sleep[i].handle = timer_wire(&callback);
	}
}

void ec_pal_timer_sleep(uint64_t until)
{
	DEBUGOUT("%d: ec_pal_timer_sleep(%llu) called", ec_tid(), until);
    unsigned idx = ec_map_timer_sleep(ec_tid());
	void* handle = ec_state_timer_sleep[idx].handle;
	setHandle(handle);
    timer_startOneShot(handle, until - timer_getNow(handle));
}

uint64_t pal_timer_getNow()
{
    unsigned idx = ec_map_timer_sleep(ec_tid());
	return timer_getNow(ec_state_timer_sleep[idx].handle);
}
