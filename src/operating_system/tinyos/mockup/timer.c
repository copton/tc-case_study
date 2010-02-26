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

static void firedHandler()
{
	timer_Callback* callback = ctx.handle;
	callback->fired(ctx.handle);
}

void timer_startPeriodic(void* handle, uint32_t dt)
{
	ctx.handle = handle;
	q_push(firedHandler);
}

