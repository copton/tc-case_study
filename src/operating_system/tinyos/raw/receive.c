#include "Receive.h"

typedef receive_Callback Callback;

typedef struct {
    int fd;
} Shared;

#include "component.h"

#include "hardware_simulation/client.h"
#include <assert.h>

void* receive_wire(receive_Callback* callback, const char* channel)
{
    Handle* handle = malloc(sizeof(Handle));
    handle->callback = callback;

    handle->shared.fd = hs_open(channel);

    setupThread(handle);
    return handle;
}

static void* run(void* h)
{
	DEBUGOUT("sensor::run(%p)", h);
    HANDLE;
    LOCK;
    SIGNAL;
	int fd = handle->shared.fd;
	UNLOCK;
	net_message_t first_msg;
    net_message_t* msg = &first_msg;
    while(1) {
		size_t res = hs_receive(fd, (unsigned*)msg, sizeof(net_message_t));
		cb_lock_acquire();
		msg = handle->callback->receive(handle, msg, &msg->buffer, res);
		cb_lock_release();
    }
	return NULL;
}
