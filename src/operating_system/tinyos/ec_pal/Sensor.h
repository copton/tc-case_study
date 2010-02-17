#ifndef CHAUQUAIHEIZIESAOVOH
#define CHAUQUAIHEIZIESAOVOH

// from tos/interfaces/Reader.nc

#include "raw/Types.h"
#include "compiler/ec.h"
#include "raw/Sensor.h"

void* pal_sensor_wire(const char* device);

//error_t sensor_read(void* handle, sensor_val_t* val);
typedef struct {
    ec_continuation_t ec_continuation;
    error_t  ec_result;
    sensor_val_t* val;
} ec_struct_sensor_read;
void ec_pal_sensor_read(void* handle);
extern ec_struct_sensor_read ec_state_sensor_read[];
unsigned ec_map_sensor_read();

#endif
