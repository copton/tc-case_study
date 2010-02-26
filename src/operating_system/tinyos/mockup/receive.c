#include "Receive.h"
#include "ReceiveInput.h"
#include "receive_init.h"
#include "Queue.h"

typedef struct {
	void* handle;
    net_message_t* msg;
} ReceiveCtx;

static ReceiveCtx ctx;
static net_message_t msg;

void mockup_receive_init()
{
    ctx.msg = &msg;
}

void* receive_wire(receive_Callback* callback, const char* channel)
{
    ctx.handle = callback; 
	return callback;
}

static void receiveHandler()
{
	receive_Callback* callback = ctx.handle;
	ctx.msg = callback->receive(ctx.handle, ctx.msg, msg.buffer, 2 * sizeof(uint32_t));
}

void receive_input()
{
    q_push(receiveHandler);
}
