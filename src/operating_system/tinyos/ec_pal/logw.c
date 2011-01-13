#include "LogWrite.h"
#include "raw/LogWrite.h"
#include <stdlib.h>

#include "component.h"

static void appendDone(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error) 
{
    DEBUGOUT("?: ec_pal_logw_append continous");
    ec_stack_logw_append* stack = load(handle);
    assert (stack!=NULL);

    if (error == SUCCESS) {
        assert (buf == stack->buf);
        *(stack->res_len) = len;
        *(stack->recordsLost) = recordsLost;
    }

    stack->ec_result = error;
    DEBUGOUT("%d: ec_pal_logw_append(...) returning", ec_tid());
    ec_events(stack->ec_cont);
}

void ec_pal_logw_append(ec_stack_logw_append* stack, void* handle, storage_len_t len)
{
    DEBUGOUT("%d: ec_pal_logw_append(...) called", ec_tid());
    error_t res = logw_append(handle, stack->buf, len);
    if (res != SUCCESS) {
        stack->ec_result = res;
        ec_events(stack->ec_cont);
    } else {
        store(handle, stack);
    }
} 

static logw_Callback callback = {&appendDone, NULL, NULL};

void* pal_logw_wire(const char* file)
{
    return logw_wire(&callback, file);
}

