#include "Send.h"
#include "raw/Send.h"
#include <stdlib.h>

#include "component.h"

static void sendDone(void* handle, net_message_t* msg, error_t error)
{
	DEBUGOUT("%d: ec_pal_send_send(...)", ec_tid());
    ec_set_tid(findThread(handle));
    assert (ec_tid() != ec_invalid_tid);
    unsigned idx = ec_map_send_send(ec_tid());

    if (error == SUCCESS) {
        assert (msg == ec_state_send_send[idx].msg);
    }

    ec_state_send_send[idx].ec_result = error;
	DEBUGOUT("%d: ec_pal_send_send(...) returns", ec_tid());
    ec_state_send_send[idx].ec_continuation();
}

void ec_pal_send_send(void* handle, uint8_t len)
{
	DEBUGOUT("%d: ec_pal_send_send(...) called", ec_tid());
    unsigned idx = ec_map_send_send();
    error_t res = send_send(handle, ec_state_send_send[idx].msg, len);
    if (res != SUCCESS) {
        ec_state_send_send[idx].ec_result = res;
        ec_state_send_send[idx].ec_continuation();
    } else {
        setHandle(handle);
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
