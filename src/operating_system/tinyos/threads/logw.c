typedef struct {
    int fd;
} State;
#include "component.h"

#include "LogWrite.h"
#include "hardware_simulation/client.h"
#include <stdlib.h>

void* logw_wire(const char* file)
{
    Handle* handle = malloc(sizeof(Handle));
    handle->state.fd = hs_open(file);
	setupThread(handle);
    return handle;
}

error_t logw_append(void* h, void* buf, storage_len_t len, storage_len_t* res_len, bool* recordsLost)
{
    HANDLE;
    ENTER;
    hs_send(handle->state.fd, buf, len);
    LEAVE;
    *res_len = len;
    *recordsLost = false;
    return SUCCESS;
}

storage_cookie_t logw_currentOffset(void* h)
{
    (void)h;
    return -1;
}

error_t logw_erase(void* h)
{
    (void)h;
    return EBUSY;
}

error_t logw_sync(void* h)
{
    (void)h;
    return EBUSY;
}
