#ifndef RAELOHNEIQUAXALIGAID
#define RAELOHNEIQUAXALIGAID

#include "Types.h"
#include "LogTypes.h"
#include "compiler/ec.h"

void* pal_logr_wire(const char* file);

//error_t logr_read(void* handle, void* buf, storage_len_t len, storage_len_t* res_len);
typedef struct {
    ec_continuation_t ec_cont;
    error_t ec_result;    
    void* buf;
    storage_len_t* res_len;
} ec_stack_logr_read;
void ec_pal_logr_read(ec_stack_logr_read* stack, void* handle, storage_len_t len);

#endif
