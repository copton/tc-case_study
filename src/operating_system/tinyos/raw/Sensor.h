#ifndef KEIXAECHIVIEHOHCHEEY
#define KEIXAECHIVIEHOHCHEEY

// from tos/interfaces/Reader.nc

#include "Types.h"

#include "SensorTypes.h"

typedef struct {
    /**
    * Signals the completion of the read().
    *
    * @param result SUCCESS if the read() was successful
    * @param val the value that has been read
    */
    void (*readDone)(void* handle, error_t result, sensor_val_t val);
} sensor_Callback;

// emulation of nesc wire statements
// the returned handle must be passed to all commands and is passed to all events
void* sensor_wire(sensor_Callback*, const char* device);

/**
* Initiates a read of the value.
*
* @return SUCCESS if a readDone() event will eventually come back.
*/
error_t sensor_read(void* handle);

#endif
