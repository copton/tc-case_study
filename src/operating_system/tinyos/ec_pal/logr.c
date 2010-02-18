#include "LogRead.h"
#include "raw/LogRead.h"
#include "infra/types.h"
#include <assert.h>
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
    ec_set_tid(findThread(handle));
    assert (ec_tid() != invalid_tid);
    unsigned idx = ec_map_logr_read();

    if (error == SUCCESS) {
        assert (buf == ec_state_logr_read[idx].buf);
        *(ec_state_logr_read[idx].res_len) = len;
    }

    ec_state_logr_read[idx].ec_result = error;
    DEBUGOUT("%d: ec_pal_logr_read(...) returns", ec_tid());
    ec_state_logr_read[idx].ec_continuation();
}

void ec_pal_logr_read(void* handle, storage_len_t len)
{
    DEBUGOUT("%d: ec_pal_logr_read(...) called", ec_tid());
    unsigned idx = ec_map_logr_read();
    error_t res = logr_read(handle, ec_state_logr_read[idx].buf, len);
    if (res != SUCCESS) {
        ec_state_logr_read[idx].ec_result = res;
        ec_state_logr_read[idx].ec_continuation();
    } else {
        setHandle(handle);
    }
}

static logr_Callback callback = {&readDone, NULL};

void* pal_logr_wire(const char* file)
{
    return logr_wire(&callback, file);
}

