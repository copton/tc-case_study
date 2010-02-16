#ifndef CHAUQUAIHEIZIESAOVOH
#define CHAUQUAIHEIZIESAOVOH

// from tos/interfaces/Reader.nc

#include "raw/Types.h"
#include "tc.h"
#include "raw/Sensor.h"

//void* sensor_wire(const char* device);
typedef struct {
    tc_continuation_t tc_continuation;
    void* tc_result;
} tc_sensor_wire_t;
void tc_pal_sensor_wire(const char* device);
extern tc_sensor_wire_t tc_state_sensor_wire[];
unsigned tc_map_sensor_wire();


//error_t sensor_read(void* handle, sensor_val_t* val);
typedef struct {
    tc_continuation_t tc_continuation;
    error_t  tc_result;
    sensor_val_t* val;
} tc_sensor_read_t;
void tc_pal_sensor_read(void* handle);
extern tc_sensor_read_t tc_state_sensor_read[];
unsigned tc_map_sensor_read();

#endif
