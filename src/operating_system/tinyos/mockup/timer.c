#include "Timer.h"
#include "Queue.h"
#include "infra/debug.h"

typedef struct {
	timer_Callback* callback;
} Handle;

static Handle handles[2];

void* timer_wire(timer_Callback* callback)
{
	static int count = 0;
	assert (count < 2);
	Handle* current = &handles[count++];
	current->callback = callback;
	return current;
}

typedef struct {
	void* handle;
} FiredContext;

static FiredContext ctx;

void firedHandler()
{
	DEBUGOUT("timer__firedHandler(): calling %p", ctx.handle);
	timer_Callback* callback = ((Handle*)ctx.handle)->callback;
	callback->fired(ctx.handle);
}

void timer_startPeriodic(void* handle, uint32_t dt)
{
	ctx.handle = handle;
	q_push(firedHandler);
}

void timer_startOneShot(void* handle, uint32_t dt)
{
	DEBUGOUT("timer_startOneShot(%p, ...)", handle);
	ctx.handle = handle;
	q_push(firedHandler);
}

uint32_t timer_getNow(void* handle)
{
	return 23;
}
