#include "Receive.h"

typedef receive_Callback Callback;

typedef struct {
    int fd;
} Shared;

#include "component.h"

#include "hardware_simulation/client.h"

void* receive_wire(receive_Callback* callback, const char* channel)
{
	DEBUGOUT("receive_wire(%p)", callback);
    Handle* handle = malloc(sizeof(Handle));
    handle->callback = callback;

    handle->shared.fd = hs_open(channel);

    setupThread(handle);
	DEBUGOUT("receive_wire(...) -> %p", handle);
    return handle;
}

static void* run(void* h)
{
	DEBUGOUT("%p: receive__run", h);
    HANDLE;
	os_sem_down();

	LOCK;
	int fd = handle->shared.fd;
	UNLOCK;
	net_message_t first_msg;
    net_message_t* msg = &first_msg;
    while(1) {
		DEBUGOUT("%p: receive__run: reading...", h);
		size_t res = hs_receive(fd, (unsigned char*)msg, sizeof(net_message_t));
		DEBUGOUT("%p: receive__run: received something", h);
		cb_lock_acquire();
		msg = handle->callback->receive(handle, msg, &msg->buffer, res);
		cb_lock_release();
    }
	return NULL;
}
