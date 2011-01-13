#include "Send.h"

typedef send_Callback Callback;

typedef struct {
    int fd;
    net_message_t* msg;
    uint8_t len;
} Shared;

#include "component.h"
#include "hardware_simulation/client.h"

void* send_wire(send_Callback* callback, const char* channel)
{
	DEBUGOUT("send_wire(%p, %s)", callback, channel);
	Handle* handle = malloc(sizeof(Handle));
	handle->callback = callback;

    handle->shared.fd = hs_open(channel);
    handle->shared.msg = NULL;
    handle->shared.len = 0;

    setupThread(handle);
	DEBUGOUT("send_wire(...) -> %p", handle);
    return handle;
}

error_t send_send(void* h, net_message_t* msg, uint8_t len)
{
    HANDLE;
    error_t res;
    LOCK;
    if (handle->shared.msg) {
        res = EBUSY;
    } else {
        handle->shared.msg = msg;
        handle->shared.len = len;
        SIGNAL;
        res = SUCCESS;
    }
    UNLOCK;
    return res;
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
    return NULL;
}


static void* run(void* h)
{
	DEBUGOUT("send__run(%p)", h);
    HANDLE;
    os_sem_down();
    LOCK;
    while(1) {
        if (handle->shared.msg == NULL) {
            DEBUGOUT("send__run i'm waiting...");
            WAIT;
            DEBUGOUT("send__run dumdidum...");
        }
        assert (handle->shared.msg);

        int fd = handle->shared.fd;
        net_message_t* msg = handle->shared.msg;
        uint8_t len = handle->shared.len;
		handle->shared.msg = NULL;
		UNLOCK;

        hs_send(fd, (unsigned char*)msg, len);

		LOCK;
		cb_lock_acquire();
		handle->callback->sendDone(handle, msg, SUCCESS);
		cb_lock_release();
	}
	UNLOCK;
	return NULL;
}
