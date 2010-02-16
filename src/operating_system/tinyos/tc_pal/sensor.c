#include "Sensor.h"
#include "raw/Sensor.h"
#include "infra/types.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, error_t result, sensor_val_t val)
{
    tc_tid = findThread(handle);
    assert (tc_tid != invalid_tid);
    unsigned idx = tc_map_sensor_read();

    if (result == SUCCESS) {
        *(tc_state_sensor_read[idx].val) = val;
    }

    tc_state_sensor_read[idx].tc_result = result;
    tc_state_sensor_read[idx].tc_continuation();
}

static sensor_Callback callback = {&readDone};

void tc_pal_sensor_wire(const char* device)
{
    unsigned idx = tc_map_sensor_wire();

    void* handle = sensor_wire(&callback, device);

    tc_state_sensor_wire[idx].tc_result = handle;
    tc_state_sensor_wire[idx].tc_continuation();
}

void tc_pal_sensor_read(void* handle)
{
    unsigned idx = tc_map_sensor_read();
    error_t res = sensor_read(handle);
    if (res != SUCCESS) {
        tc_state_sensor_read[idx].tc_result = res;
        tc_state_sensor_read[idx].tc_continuation();
    } else {
        setHandle(handle);
    }
}

