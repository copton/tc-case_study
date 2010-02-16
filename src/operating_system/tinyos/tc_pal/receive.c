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

static receive_Callback callback = {&receive};

void tc_pal_receive_wire(const char* channel)
{
    unsigned idx = tc_map_receive_wire();
    void* handle = receive_wire(&callback, channel);

    tc_state_receive_wire[idx].tc_result = handle;
    tc_state_receive_wire[idx].tc_continuation();
}

void tc_pal_receive_receive(void* handle)
{
    setHandle(handle);
} 
