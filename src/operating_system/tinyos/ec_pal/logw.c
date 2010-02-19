#include "LogWrite.h"
#include "raw/LogWrite.h"
#include <stdlib.h>

#include "component.h"

static void appendDone(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error) 
{
    DEBUGOUT("%d: ec_pal_logw_append(...)", ec_tid());
    ec_set_tid(findThread(handle));
    assert(ec_tid() != ec_invalid_tid);
    unsigned idx = ec_map_logw_append(ec_tid());

    if (error == SUCCESS) {
        assert (buf == ec_state_logw_append[idx].buf);
        *(ec_state_logw_append[idx].res_len) = len;
        *(ec_state_logw_append[idx].recordsLost) = recordsLost;
    }

    ec_state_logw_append[idx].ec_result = error;
    DEBUGOUT("%d: ec_pal_logw_append(...) returning", ec_tid());
    ec_state_logw_append[idx].ec_continuation();
}

void ec_pal_logw_append(void* handle, storage_len_t len)
{
    DEBUGOUT("%d: ec_pal_logw_append(...) called", ec_tid());
    unsigned idx = ec_map_logw_append();
    error_t res = logw_append(handle, ec_state_logw_append[idx].buf, len);
    if (res != SUCCESS) {
        ec_state_logw_append[idx].ec_result = res;
        ec_state_logw_append[idx].ec_continuation();
    } else {
        setHandle(handle);
    }
} 

static logw_Callback callback = {&appendDone, NULL, NULL};

void* pal_logw_wire(const char* file)
{
    return logw_wire(&callback, file);
}

