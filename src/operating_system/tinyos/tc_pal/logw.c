#include "LogWrite.h"
#include "raw/LogWrite.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void appendDone(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error) 
{
    tc_tid = findThread(handle);
    assert(tc_tid != invalid_tid);
    unsigned idx = tc_map_logw_append(tc_tid);

    if (error == SUCCESS) {
        assert (buf == tc_state_logw_append[idx].buf);
        *(tc_state_logw_append[idx].res_len) = len;
        *(tc_state_logw_append[idx].recordsLost) = recordsLost;
    }

    tc_state_logw_append[idx].tc_result = error;
    tc_state_logw_append[idx].tc_continuation();
}

static logw_Callback callback = {&appendDone, NULL, NULL};

void tc_pal_logw_wire(const char* file)
{
    unsigned idx = tc_map_logw_wire();

    void* handle = logw_wire(&callback, file);

    tc_state_logw_wire[idx].tc_result = handle;
    tc_state_logw_wire[idx].tc_continuation();
}

void tc_pal_logw_append(void* handle, storage_len_t len)
{
    unsigned idx = tc_map_logw_append();
    error_t res = logw_append(handle, tc_state_logw_append[idx].buf, len);
    if (res != SUCCESS) {
        tc_state_logw_append[idx].tc_result = res;
        tc_state_logw_append[idx].tc_continuation();
    } else {
        setHandle(handle);
    }
} 
