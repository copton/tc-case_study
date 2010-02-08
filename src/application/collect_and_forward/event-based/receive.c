#include "receive.h"

#include <stdio.h>

#include "timer.h"

void* handle = NULL;

static void fired(void* handle)
{
    printf("fired\n");
}

timer_Callback callback = {&fired};

void receive_init()
{
    handle = timer_wire(&callback);
    timer_startPeriodic(handle, 1000);
}
