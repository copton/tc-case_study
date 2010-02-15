typedef struct {
    int fd;
} State;

#include "component.h"

#include "LogRead.h"
#include "hardware_simulation/client.h"
#include <stdlib.h>


void* logr_wire(const char* file)
{
    Handle* handle = malloc(sizeof(Handle));
    handle->state.fd = hs_open(file);
	setupThread(handle);
    return handle;
}

error_t logr_read(void* h, void* buf, storage_len_t len, storage_len_t* res_len)
{
    HANDLE;
	ENTER;
    *res_len = hs_read(handle->state.fd, buf, len);
	LEAVE;
    return SUCCESS;
}


storage_cookie_t logr_currentOffset(void* h)
{
    (void)h;
    return -1;
}

error_t logr_seek(void* h, storage_cookie_t offset)
{
    (void)h;
    (void)offset;
    return EBUSY;
}

storage_len_t logr_getSize(void* h)
{
    return (unsigned)-1;
}
