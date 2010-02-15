typedef struct {
    int fd;
} State;

#include "component.h"

#include "Receive.h"
#include "hardware_simulation/client.h"
#include <stdlib.h>
#include <assert.h>

void* receive_wire(const char* channel)
{
    Handle* handle = malloc(sizeof(Handle));
    handle->state.fd = hs_open(channel);
	setupThread(handle);
    return handle;
}

error_t receive_receive(void* h, net_message_t* msg, void** payload, uint8_t* len)
{
    HANDLE;
    ENTER;

    *len = hs_receive(handle->state.fd, (unsigned char*)msg, sizeof(net_message_t));
    LEAVE;

    *payload = &msg->buffer;
    return SUCCESS;
}

error_t send_cancel(void* handle, net_message_t* msg)
{
    (void)handle;
    (void)msg;
    return FAIL;
}

uint8_t send_maxPayloadLength(void* handle)
{
    (void)handle;
    return net_buffer_size;
}

void* send_getPayload(void* handle, net_message_t* msg, uint8_t len)
{
    (void)handle;
    if (len < net_buffer_size) {
        return msg->buffer;
    } else {
        return NULL;
    }
}
