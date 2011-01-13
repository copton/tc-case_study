#include "LogRead.h"
#include "raw/LogRead.h"
#include "infra/types.h"
#include <stdlib.h>

#include "component.h"

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
    DEBUGOUT("?: ec_pal_logr_read continous");
    ec_stack_logr_read* stack = load(handle);
    assert(stack!=NULL);

    if (error == SUCCESS) {
        assert (buf == stack->buf);
        *(stack->res_len) = len;
    }

    stack->ec_result = error;
    DEBUGOUT("%d: ec_pal_logr_read(...) returns", ec_tid());
    ec_events(stack->ec_cont);
}

void ec_pal_logr_read(ec_stack_logr_read* stack, void* handle, storage_len_t len)
{
    DEBUGOUT("%d: ec_pal_logr_read(...) called", ec_tid());
    error_t res = logr_read(handle, stack->buf, len);
    if (res != SUCCESS) {
        stack->ec_result = res;
        ec_events(stack->ec_cont);
    } else {
        store(handle, stack);
    }
}

static logr_Callback callback = {&readDone, NULL};

void* pal_logr_wire(const char* file)
{
    return logr_wire(&callback, file);
}

