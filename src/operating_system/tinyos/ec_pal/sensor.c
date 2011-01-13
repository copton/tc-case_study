#include "Sensor.h"
#include "raw/Sensor.h"
#include "infra/types.h"
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, error_t result, sensor_val_t val)
{
    DEBUGOUT("?: ec_pal_sensor_read continous");
    ec_stack_sensor_read* stack = load(handle);
    assert (stack != NULL);

    if (result == SUCCESS) {
        *(stack->val) = val;
    }

    stack->ec_result = result;
    DEBUGOUT("%d: ec_pal_sensor_read(...) returns", ec_tid());
    ec_events(stack->ec_cont);
}

void ec_pal_sensor_read(ec_stack_sensor_read* stack, void* handle)
{
    DEBUGOUT("%d: ec_pal_sensor_read(...) called", ec_tid());
    error_t res = sensor_read(handle);
    if (res != SUCCESS) {
        stack->ec_result = res;
        ec_events(stack->ec_cont);
    } else {
        store(handle, stack);
    }
}

static sensor_Callback callback = {&readDone};

void* pal_sensor_wire(const char* device)
{
    return sensor_wire(&callback, device);
}
