#include "Sensor.h"
#include "raw/Sensor.h"
#include "infra/types.h"
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, error_t result, sensor_val_t val)
{
    DEBUGOUT("%d: ec_pal_sensor_read(...)", ec_tid());
    ec_set_tid(findThread(handle));
    assert (ec_tid() != ec_invalid_tid);
	ec_struct_sensor_read*const ec_p_sensor_read = ec_map_sensor_read();

    if (result == SUCCESS) {
        *(ec_p_sensor_read->val) = val;
    }

    ec_p_sensor_read->ec_result = result;
    DEBUGOUT("%d: ec_pal_sensor_read(...) returns", ec_tid());
    ec_p_sensor_read->ec_continuation();
}

void ec_pal_sensor_read(void* handle)
{
    DEBUGOUT("%d: ec_pal_sensor_read(...) called", ec_tid());
	ec_struct_sensor_read*const ec_p_sensor_read = ec_map_sensor_read();
    error_t res = sensor_read(handle);
    if (res != SUCCESS) {
        ec_p_sensor_read->ec_result = res;
        ec_p_sensor_read->ec_continuation();
    } else {
        setHandle(handle);
    }
}

static sensor_Callback callback = {&readDone};

void* pal_sensor_wire(const char* device)
{
    return sensor_wire(&callback, device);
}
