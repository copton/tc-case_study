#include "LogRead.h"
#include "raw/LogRead.h"
#include "infra/types.h"
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
    DEBUGOUT("%d: ec_pal_logr_read(...)", ec_tid());
    ec_set_tid(findThread(handle));
    assert (ec_tid() != ec_invalid_tid);
	ec_struct_logr_read*const ec_p_logr_read = ec_map_logr_read();

    if (error == SUCCESS) {
        assert (buf == ec_p_logr_read->buf);
        *(ec_p_logr_read->res_len) = len;
    }

    ec_p_logr_read->ec_result = error;
    DEBUGOUT("%d: ec_pal_logr_read(...) returns", ec_tid());
    ec_p_logr_read->ec_continuation();
}

void ec_pal_logr_read(void* handle, storage_len_t len)
{
    DEBUGOUT("%d: ec_pal_logr_read(...) called", ec_tid());
	ec_struct_logr_read*const ec_p_logr_read = ec_map_logr_read();
    error_t res = logr_read(handle, ec_p_logr_read->buf, len);
    if (res != SUCCESS) {
        ec_p_logr_read->ec_result = res;
        ec_p_logr_read->ec_continuation();
    } else {
        setHandle(handle);
    }
}

static logr_Callback callback = {&readDone, NULL};

void* pal_logr_wire(const char* file)
{
    return logr_wire(&callback, file);
}

