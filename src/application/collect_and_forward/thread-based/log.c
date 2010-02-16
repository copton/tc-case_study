#include "log.h"
#include <assert.h>
#include "infra/types.h"
#include "LogWrite.h"

void log_to(void* handle, void* buf, storage_len_t len)
{
    storage_len_t res_len;
    bool recordsLost;
    error_t res = logw_append(handle, buf, len, &res_len, &recordsLost);
    assert (res == SUCCESS);
    assert (res_len == len);
}
