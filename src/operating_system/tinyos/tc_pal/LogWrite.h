#ifndef OOPHEIWOHXAISEFOOTOO
#define OOPHEIWOHXAISEFOOTOO

#include "raw/Types.h"
#include "raw/Log.h"
#include "tc.h"

//void* logw_wire(const char* file);
typedef struct {
    tc_continuation_t tc_continuation;
    void* tc_result;
} tc_logw_wire_t;
void tc_pal_logw_wire(const char* file);
extern tc_logw_wire_t tc_state_logw_wire[];
unsigned tc_map_logw_wire();

//error_t logw_append(void* handle, void* buf, storage_len_t len, storage_len_t* res_len, bool* recordsLost);
typedef struct {
    tc_continuation_t tc_continuation;
    error_t tc_result;    
    void* buf;
    storage_len_t* res_len;
    bool* recordsLost;
} tc_logw_append_t;
void tc_pal_logw_append(void* handle, storage_len_t len);
extern tc_logw_append_t tc_state_logw_append[];
unsigned tc_map_logw_append();

#endif
