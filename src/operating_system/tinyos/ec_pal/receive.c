#include "Receive.h"
#include "raw/Receive.h"
#include <stdlib.h>
#include <string.h>

#include "component.h"

static net_message_t* receive(void* handle, net_message_t* msg, void* payload, uint8_t len)
{
	DEBUGOUT("%d: ec_pal_receive_receive(...)", ec_tid());
    ec_set_tid(findThread(handle));
    if (ec_tid() != ec_invalid_tid) {
        ec_struct_receive_receive*const ec_p_receive_receive = ec_map_receive_receive();

        ec_p_receive_receive->ec_result = SUCCESS;
        memcpy(ec_p_receive_receive->msg, msg, sizeof(net_message_t));
        *ec_p_receive_receive->payload = payload;
        *ec_p_receive_receive->len = len;
		DEBUGOUT("%d: ec_pal_receive_receive(...) returning", ec_tid());
        ec_p_receive_receive->ec_continuation();
    } else {
		DEBUGOUT("ec_pal_receive_receive(...) -> ignoring message");
    }
    return msg;
}

void ec_pal_receive_receive(void* handle)
{
	DEBUGOUT("%d: ec_pal_receive_receive(...)", ec_tid());
    setHandle(handle);
} 

static receive_Callback callback = {&receive};

void* pal_receive_wire(const char* channel)
{
    return receive_wire(&callback, channel);
}

