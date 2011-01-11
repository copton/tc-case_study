#ifndef CHAUQUAIHEIZIESAOVOH
#define CHAUQUAIHEIZIESAOVOH

// from tos/interfaces/Reader.nc

#include "Types.h"
#include "compiler/ec.h"
#include "SensorTypes.h"

void* pal_sensor_wire(const char* device);

//error_t sensor_read(void* handle, sensor_val_t* val);
typedef struct {
    ec_continuation_t ec_cont;
    error_t  ec_result;
    sensor_val_t* val;
} ec_stack_sensor_read;
void ec_pal_sensor_read(ec_stack_sensor_read* stack, void* handle);

#endif
