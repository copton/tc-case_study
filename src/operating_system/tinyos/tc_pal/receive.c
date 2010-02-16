#include "Receive.h"
#include "raw/Receive.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static net_message_t* receive(void* handle, net_message_t* msg, void* payload, uint8_t len)
{
    tc_tid = findThread(handle);
    if (tc_tid != invalid_tid) {
        *tc_state_receive_receive[tc_tid].msg = msg;
        *tc_state_receive_receive[tc_tid].payload = payload;
        *tc_state_receive_receive[tc_tid].len = len;
        tc_state_receive_receive[tc_tid].tc_continuation();
    }

    return msg;
}

void tc_pal_receive_receive(void* handle)
{
    setHandle(handle);
} 

static receive_Callback callback = {&receive};

void* pal_receive_wire(const char* channel)
{
    return receive_wire(&callback, channel);
}

