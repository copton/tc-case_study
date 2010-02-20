#include "LogWrite.h"
#include "raw/LogWrite.h"
#include <stdlib.h>

#include "component.h"

static void appendDone(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error) 
{
    DEBUGOUT("%d: ec_pal_logw_append(...)", ec_tid());
    ec_set_tid(findThread(handle));
    assert(ec_tid() != ec_invalid_tid);
	ec_struct_logw_append*const ec_p_logw_append = ec_map_logw_append();

    if (error == SUCCESS) {
        assert (buf == ec_p_logw_append->buf);
        *(ec_p_logw_append->res_len) = len;
        *(ec_p_logw_append->recordsLost) = recordsLost;
    }

    ec_p_logw_append->ec_result = error;
    DEBUGOUT("%d: ec_pal_logw_append(...) returning", ec_tid());
    ec_p_logw_append->ec_continuation();
}

void ec_pal_logw_append(void* handle, storage_len_t len)
{
    DEBUGOUT("%d: ec_pal_logw_append(...) called", ec_tid());
	ec_struct_logw_append*const ec_p_logw_append = ec_map_logw_append();
    error_t res = logw_append(handle, ec_p_logw_append->buf, len);
    if (res != SUCCESS) {
        ec_p_logw_append->ec_result = res;
        ec_p_logw_append->ec_continuation();
    } else {
        setHandle(handle);
    }
} 

static logw_Callback callback = {&appendDone, NULL, NULL};

void* pal_logw_wire(const char* file)
{
    return logw_wire(&callback, file);
}

