#include "Timer.h"
#include "raw/Timer.h"
#include "infra/debug.h"

#include "component.h"

static void fired(void* handle)
{
	DEBUGOUT("%d: ec_pal_timer_sleep()", ec_tid());
    ec_set_tid(findThread(handle));
	ec_struct_timer_sleep*const ec_p_timer_sleep = ec_map_timer_sleep();
	DEBUGOUT("%d: ec_pal_timer_sleep() returns", ec_tid());
    ec_p_timer_sleep->ec_continuation();
}

static timer_Callback callback = {&fired};


void ec_pal_timer_sleep(void* handle, uint32_t until)
{
	DEBUGOUT("%d: ec_pal_timer_sleep(%p, %llu) called", ec_tid(), handle, until);
	setHandle(handle);
	uint32_t now = timer_getNow(handle);
	uint32_t diff;
	if (until > now) {
		diff = until - now;
	} else {
		diff = until + (0xFFFFFFFF - now);
	}
    timer_startOneShot(handle, until - timer_getNow(handle));
}

uint32_t pal_timer_getNow(void* handle)
{
	return timer_getNow(handle);
}

void* pal_timer_wire()
{
	return timer_wire(&callback);	
}

