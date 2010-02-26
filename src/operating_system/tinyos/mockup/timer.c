#include "Timer.h"
#include "Queue.h"

void* timer_wire(timer_Callback* callback)
{
	return callback;	
}

typedef struct {
	void* handle;
} FiredContext;

static FiredContext ctx;

void firedHandler()
{
	timer_Callback* callback = ctx.handle;
	callback->fired(ctx.handle);
}

void timer_startPeriodic(void* handle, uint32_t dt)
{
	ctx.handle = handle;
	q_push(firedHandler);
}

void timer_startOneShot(void* handle, uint32_t dt)
{
	ctx.handle = handle;
	q_push(firedHandler);
}

uint32_t timer_getNow(void* handle)
{
	return 23;
}
