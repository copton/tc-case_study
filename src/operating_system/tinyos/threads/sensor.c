typedef struct {
    int fd;
} State;

#include "component.h"

#include "Sensor.h"
#include "hardware_simulation/client.h"
#include <stdlib.h>

void* sensor_wire(const char* device)
{
    Handle* handle = malloc(sizeof(Handle));
    handle->state.fd = hs_open(device);
	setupThread(handle);
    return handle;
}

error_t sensor_read(void* h, sensor_val_t* val)
{
    HANDLE;
    ENTER;

    size_t res = hs_read(handle->state.fd, (unsigned char*)val, sizeof(sensor_val_t));
    assert (res == sizeof(sensor_val_t));
    
    LEAVE;
    return SUCCESS;
}
