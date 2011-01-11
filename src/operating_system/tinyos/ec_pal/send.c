#include "Send.h"
#include "raw/Send.h"
#include <stdlib.h>

#include "component.h"

static void sendDone(void* handle, net_message_t* msg, error_t error)
{
	DEBUGOUT("%d: ec_pal_send_send(...)", ec_tid());
    ec_stack_send_send* stack = load(handle);
    assert (stack != NULL);

    if (error == SUCCESS) {
        assert (msg == stack->msg);
    }

    stack->ec_result = error;
	DEBUGOUT("%d: ec_pal_send_send(...) returns", ec_tid());
    ec_events(stack->ec_cont);
}

void ec_pal_send_send(ec_stack_send_send* stack, void* handle, uint8_t len)
{
	DEBUGOUT("%d: ec_pal_send_send(...) called", ec_tid());
    error_t res = send_send(handle, stack->msg, len);
    if (res != SUCCESS) {
        stack->ec_result = res;
        ec_events(stack->ec_cont);
    } else {
        store(handle, stack);
    }
} 

static send_Callback callback = {&sendDone};

void* pal_send_wire(const char* channel)
{
    return send_wire(&callback, channel);
}

void* pal_send_getPayload(void* handle, net_message_t* msg, uint8_t len)
{
    return send_getPayload(handle, msg, len);
}
