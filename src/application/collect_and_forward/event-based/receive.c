#include "receive.h"

#include <stdio.h>
#include <assert.h>

#include "Receive.h"
#include "infra/debug.h"

void* receive_handle = NULL;

static net_message_t* receive(void* handle, net_message_t* msg, void* payload, uint8_t len)
{
    printf("receive::receive(%p, ...)\n", handle);
	assert (handle == receive_handle);
    return msg;
}

receive_Callback callback = {&receive};

void receive_init(const char* channel, const char* file)
{
	DEBUGOUT("receive_init(%s, %s)\n", channel, file);
    receive_handle = receive_wire(&callback, channel);
}
