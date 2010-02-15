#include "LogWrite.h"
#include "raw/LogWrite.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void appendDone(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error) 
{
    tid_t tid = findThread(handle);
    unsigned idx = tc_map_logw_append(tid);

    if (error == SUCCESS) {
        assert (buf == tc_state_logw_append[idx].buf);
        *(tc_state_logw_append[idx].res_len) = len;
        *(tc_state_logw_append[idx].recordsLost) = recordsLost;
    }

    tc_state_logw_append[idx].tc_result = error;
    tc_state_logw_append[idx].tc_continuation(tid);
}

static logw_Callback callback = {&appendDone, NULL, NULL};

void tc_pal_logw_wire(tid_t tid, const char* file)
{
    unsigned idx = tc_map_logw_wire(tid);

    handles[tid] = logw_wire(&callback, file);

    tc_state_logr_wire[idx].tc_result = handles[tid];
    tc_state_logr_wire[idx].tc_continuation(tid);
}

void tc_pal_logw_append(tid_t tid, void* handle, storage_len_t len)
{
    unsigned idx = tc_map_logw_append(tid);
    error_t res = logw_append(handle, tc_state_logw_append[idx].buf, len);
    if (res != SUCCESS) {
        tc_state_logw_append[idx].tc_result = res;
        tc_state_logw_append[idx].tc_continuation(tid);
    }
} 
