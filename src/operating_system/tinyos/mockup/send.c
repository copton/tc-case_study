#include "Send.h"
#include "Queue.h"

void* send_wire(send_Callback* callback, const char* channel)
{
	return callback;	
}

typedef struct {
	void* handle;
	net_message_t* msg;
} SendDoneCtx;

static SendDoneCtx ctx;

static void sendDoneHandler()
{
	send_Callback* callback = ctx.handle;
	callback->sendDone(ctx.handle, ctx.msg, SUCCESS);
}

error_t send_send(void* handle, net_message_t* msg, uint8_t len)
{
	ctx.handle = handle;
    ctx.msg = msg;
	q_push(sendDoneHandler);
    return SUCCESS;
}

void* send_getPayload(void* handle, net_message_t* msg, uint8_t len)
{
    return msg->buffer;
}
