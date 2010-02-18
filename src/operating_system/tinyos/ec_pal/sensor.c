#include "Sensor.h"
#include "raw/Sensor.h"
#include "infra/types.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, error_t result, sensor_val_t val)
{
    ec_set_tid(findThread(handle));
    assert (ec_tid() != invalid_tid);
    unsigned idx = ec_map_sensor_read();

    if (result == SUCCESS) {
        *(ec_state_sensor_read[idx].val) = val;
    }

    ec_state_sensor_read[idx].ec_result = result;
    DEBUGOUT("%d: ec_pal_sensor_read(...) returns", ec_tid());
    ec_state_sensor_read[idx].ec_continuation();
}

void ec_pal_sensor_read(void* handle)
{
    DEBUGOUT("%d: ec_pal_sensor_read(...) called", ec_tid());
    unsigned idx = ec_map_sensor_read();
    error_t res = sensor_read(handle);
    if (res != SUCCESS) {
        ec_state_sensor_read[idx].ec_result = res;
        ec_state_sensor_read[idx].ec_continuation();
    } else {
        setHandle(handle);
    }
}

static sensor_Callback callback = {&readDone};

void* pal_sensor_wire(const char* device)
{
    return sensor_wire(&callback, device);
}
