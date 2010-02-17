#include "Receive.h"
#include "raw/Receive.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static net_message_t* receive(void* handle, net_message_t* msg, void* payload, uint8_t len)
{
    ec_tid = findThread(handle);
    if (ec_tid != invalid_tid) {
        ec_struct_receive_receive* ec_p_receive_receive = &ec_state_receive_receive[ec_map_receive_receive(ec_tid)];

        net_message_t* res = ec_p_receive_receive->cur_msg;
        ec_p_receive_receive->cur_msg = msg;

        ec_p_receive_receive->ec_result = SUCCESS;
        *ec_p_receive_receive->msg = msg;
        *ec_p_receive_receive->payload = payload;
        *ec_p_receive_receive->len = len;
        ec_p_receive_receive->ec_continuation();
        return res;
    } else {
        return msg;
    }
}

void ec_pal_receive_receive(void* handle)
{
    setHandle(handle);
} 

static receive_Callback callback = {&receive};

void* pal_receive_wire(const char* channel)
{
    ec_struct_receive_receive* ec_p_receive_receive = &ec_state_receive_receive[ec_map_receive_receive(ec_tid)];
    ec_p_receive_receive->cur_msg = &ec_p_receive_receive->other_msg;

    return receive_wire(&callback, channel);
}

