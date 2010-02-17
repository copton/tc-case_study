#ifndef IECEIXOATHECHEIHEENG
#define IECEIXOATHECHEIHEENG

/*
#include "Log.h"

void log_to(void* handle, void* buf, storage_len_t len);
*/

#include "compiler/ec.h"
#include "Log.h"

typedef struct {
    ec_continuation_t ec_continuation;
} ec_struct_log_to;
void log_to(void* handle, void* buf, storage_len_t len);

extern ec_struct_log_to ec_state_log_to[];
unsigned ec_map_log_to();

#endif
