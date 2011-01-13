#include "Receive.h"
#include "raw/Receive.h"
#include <stdlib.h>
#include <string.h>

#include "component.h"

static net_message_t* receive(void* handle, net_message_t* msg, void* payload, uint8_t len)
{
	DEBUGOUT("?: ec_pal_receive_receive continous");
    ec_stack_receive_receive* stack = load(handle);  
    if (stack != NULL) {
        stack->ec_result = SUCCESS;
        memcpy(stack->msg, msg, sizeof(net_message_t));
        *stack->payload = payload;
        *stack->len = len;
		DEBUGOUT("%d: ec_pal_receive_receive(...) returning", ec_tid());
        ec_events(stack->ec_cont);
    } else {
		DEBUGOUT("ec_pal_receive_receive(...) -> ignoring message");
    }
    return msg;
}

void ec_pal_receive_receive(ec_stack_receive_receive* stack, void* handle)
{
	DEBUGOUT("%d: ec_pal_receive_receive(...)", ec_tid());
    store(handle, stack);
} 

static receive_Callback callback = {&receive};

void* pal_receive_wire(const char* channel)
{
    return receive_wire(&callback, channel);
}

