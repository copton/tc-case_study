#ifndef CHAUQUAIHEIZIESAOVOH
#define CHAUQUAIHEIZIESAOVOH

// from tos/interfaces/Reader.nc

#include "raw/Types.h"
#include "tc.h"
#include "raw/Sensor.h"

void* pal_sensor_wire(const char* device);

//error_t sensor_read(void* handle, sensor_val_t* val);
typedef struct {
    tc_continuation_t tc_continuation;
    error_t  tc_result;
    sensor_val_t* val;
} tc_struct_sensor_read;
void tc_pal_sensor_read(void* handle);
extern tc_struct_sensor_read tc_state_sensor_read[];
unsigned tc_map_sensor_read();

#endif
