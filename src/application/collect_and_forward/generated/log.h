#ifndef IECEIXOATHECHEIHEENG
#define IECEIXOATHECHEIHEENG

#include "Log.h"

typedef struct {
    tc_continuation_t tc_continuation;
} tc_struct_log_to;

void log_to(void* handle, void* buf, storage_len_t len);

#endif
