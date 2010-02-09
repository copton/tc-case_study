#include "receive.h"

#include <stdio.h>
#include <assert.h>

#include "Timer.h"
#include "infra/debug.h"

void* receive_handle = NULL;

static void fired(void* handle)
{
    printf("receive::fired(%p)\n", handle);
	assert (handle == receive_handle);
}

timer_Callback callback = {&fired};

void receive_init()
{
	DEBUGOUT("receive_init()\n");
    receive_handle = timer_wire(&callback);
    timer_startPeriodic(receive_handle, 1000);
}
