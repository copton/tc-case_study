#include "Timer.h"
#include "raw/Timer.h"
#include "infra/debug.h"

#include "component.h"

static void fired(void* handle)
{
	DEBUGOUT("?: ec_pal_timer_sleep continues");
    ec_stack_timer_sleep* stack = load(handle);
	assert (stack != NULL);
	DEBUGOUT("%d: ec_pal_timer_sleep() returns", ec_tid());
    ec_events(stack->ec_cont);
}

static timer_Callback callback = {&fired};

void ec_pal_timer_sleep(ec_stack_timer_sleep* stack, void* handle, uint32_t until)
{
	DEBUGOUT("%d: ec_pal_timer_sleep(%p, %llu) called", ec_tid(), handle, until);
	store(handle, stack);
	const uint32_t now = timer_getNow(handle);
	uint32_t diff;
	if (until > now) {
		diff = until - now;
	} else {
		diff = until + (0xFFFFFFFF - now);
	}
    timer_startOneShot(handle, diff);
}

uint32_t pal_timer_getNow(void* handle)
{
	return timer_getNow(handle);
}

void* pal_timer_wire()
{
	return timer_wire(&callback);	
}

