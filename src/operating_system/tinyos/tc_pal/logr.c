#include "LogRead.h"
#include "raw/LogRead.h"
#include "infra/types.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
    tc_tid = findThread(handle);
    assert (tc_tid != invalid_tid);
    unsigned idx = tc_map_logr_read();

    if (error == SUCCESS) {
        assert (buf == tc_state_logr_read[idx].buf);
        *(tc_state_logr_read[idx].res_len) = len;
    }

    tc_state_logr_read[idx].tc_result = error;
    tc_state_logr_read[idx].tc_continuation();
}

void tc_pal_logr_read(void* handle, storage_len_t len)
{
    unsigned idx = tc_map_logr_read();
    error_t res = logr_read(handle, tc_state_logr_read[idx].buf, len);
    if (res != SUCCESS) {
        tc_state_logr_read[idx].tc_result = res;
        tc_state_logr_read[idx].tc_continuation();
    } else {
        setHandle(handle);
    }
}

static logr_Callback callback = {&readDone, NULL};

void* pal_logr_wire(const char* file)
{
    return logr_wire(&callback, file);
}

