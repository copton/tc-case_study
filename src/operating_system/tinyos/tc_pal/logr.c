#include "LogRead.h"
#include "raw/LogRead.h"
#include "infra/types.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
    tid_t tid = findThread(handle);
    unsigned idx = tc_map_logr_read(tid);

    if (error == SUCCESS) {
        assert (buf == tc_state_logr_read[idx].buf);
        *(tc_state_logr_read[idx].res_len) = len;
    }

    tc_state_logr_read[idx].tc_result = error;
    tc_state_logr_read[idx].tc_continuation(tid);
}

static logr_Callback callback = {&readDone, NULL};

void tc_pal_logr_wire(tid_t tid, const char* file)
{
    unsigned idx = tc_map_logr_wire(tid);

    handles[tid] = logr_wire(&callback, file);

    tc_state_logr_wire[idx].tc_result = handles[tid];
    tc_state_logr_wire[idx].tc_continuation(tid);
}

void tc_pal_logr_read(tid_t tid, void* handle, storage_len_t len)
{
    unsigned idx = tc_map_logr_read(tid);
    error_t res = logr_read(handle, tc_state_logr_read[idx].buf, len);
    if (res != SUCCESS) {
        tc_state_logr_read[idx].tc_result = res;
        tc_state_logr_read[idx].tc_continuation(tid);
    }
}

