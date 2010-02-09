#include "collect.h"

#include "timer.h"
#include "sensor.h"

#include "infra/debug.h"

#include <assert.h>

void* timer_handle = NULL;
void* sensor_handle = NULL;

static void fired(void* handle)
{
    assert(handle == timer_handle);
    error_t res = sensor_read(sensor_handle);
    assert (res == SUCCESS);
}

static void readDone(void* handle, error_t error, sensor_val_t value)
{
    DEBUGOUT("sensor value %d\n", value); 
}

timer_Callback timer_callback = {&fired};
sensor_Callback sensor_callback = {&readDone};

void collect_init(const char* sensor, const char* file)
{
	DEBUGOUT("collect_init\n");
    timer_handle = timer_wire(&timer_callback);
    sensor_handle = sensor_wire(&sensor_callback, sensor);
    timer_startPeriodic(timer_handle, 1000);
}
