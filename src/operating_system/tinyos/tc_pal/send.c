#include "Send.h"
#include "raw/Send.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void sendDone(void* handle, net_message_t* msg, error_t error)
{
    tc_tid = findThread(handle);
    assert (tc_tid != invalid_tid);
    unsigned idx = tc_map_send_send(tc_tid);

    if (error == SUCCESS) {
        assert (msg == tc_state_send_send[idx].msg);
    }

    tc_state_send_send[idx].tc_result = error;
    tc_state_send_send[idx].tc_continuation();
}

static send_Callback callback = {&sendDone};

void tc_pal_send_wire(const char* channel)
{
    unsigned idx = tc_map_send_wire();

    void* handle = send_wire(&callback, channel);

    tc_state_send_wire[idx].tc_result = handle;
    tc_state_send_wire[idx].tc_continuation();
}

void tc_pal_send_send(void* handle, uint8_t len)
{
    unsigned idx = tc_map_send_send();
    error_t res = send_send(handle, tc_state_send_send[idx].msg, len);
    if (res != SUCCESS) {
        tc_state_send_send[idx].tc_result = res;
        tc_state_send_send[idx].tc_continuation();
    } else {
        setHandle(handle);
    }
} 
