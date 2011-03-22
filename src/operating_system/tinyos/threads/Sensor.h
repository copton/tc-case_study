#ifndef UQUOOFULEEBEIKAIGHAI
#define UQUOOFULEEBEIKAIGHAI

// from tos/interfaces/Reader.nc

#include "compiler/tc.h"
#include "Types.h"
#include "SensorTypes.h"


// emulation of nesc wire statements
// the returned handle must be passed to all commands
void* sensor_wire(const char* device);

/**
* Read the value.
*
* @param val the value that has been read
* @return 
*   <li>SUCCESS if the read() was successful
*   <li>EBUSY if a request is already being processed.
*/
TC_BLOCKING error_t sensor_read(void* handle, sensor_val_t* val);

#endif
