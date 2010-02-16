#ifndef OOPHEIWOHXAISEFOOTOO
#define OOPHEIWOHXAISEFOOTOO

#include "raw/Types.h"
#include "raw/Log.h"
#include "tc.h"

void* pal_logw_wire(const char* file);

//error_t logw_append(void* handle, void* buf, storage_len_t len, storage_len_t* res_len, bool* recordsLost);
typedef struct {
    tc_continuation_t tc_continuation;
    error_t tc_result;    
    void* buf;
    storage_len_t* res_len;
    bool* recordsLost;
} tc_struct_logw_append;
void tc_pal_logw_append(void* handle, storage_len_t len);
extern tc_struct_logw_append tc_state_logw_append[];
unsigned tc_map_logw_append();

#endif
