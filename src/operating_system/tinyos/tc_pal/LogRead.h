#ifndef RAELOHNEIQUAXALIGAID
#define RAELOHNEIQUAXALIGAID

#include "raw/Types.h"
#include "raw/Log.h"
#include "tc.h"

void* pal_logr_wire(const char* file);

//error_t logr_read(void* handle, void* buf, storage_len_t len, storage_len_t* res_len);
typedef struct {
    tc_continuation_t tc_continuation;
    error_t tc_result;    
    void* buf;
    storage_len_t* res_len;
} tc_struct_logr_read;
void tc_pal_logr_read(void* handle, storage_len_t len);
extern tc_struct_logr_read tc_state_logr_read[];
unsigned tc_map_logr_read();

#endif
