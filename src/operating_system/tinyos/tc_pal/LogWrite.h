#ifndef XOREECEOBEKENGIEQUID
#define XOREECEOBEKENGIEQUID

#include "raw/Types.h"
#include "raw/Log.h"
#include "tc.h"

//void* logw_wire(const char* file);
typedef struct {
    tc_continuation_t tc_continuation;
    void* tc_result;
} tc_logw_wire_t;
extern tc_logw_wire_t tc_state_logw_wire[];
unsigned tc_map_logw_wire(tid_t);
void tc_pal_logw_wire(tid_t, const char* file);

//error_t logw_append(void* handle, void* buf, storage_len_t len, storage_len_t* res_len, bool* recordsLost);
typedef struct {
    tc_continuation_t tc_continuation;
    void* buf;
    storage_len_t* res_len;
    bool* recordsLost;
    error_t tc_result;    
} tc_logw_append_t;
extern tc_logw_append_t tc_state_logw_append[];
void tc_pal_logw_append(tid_t tid, void* handle, storage_len_t len);
unsigned tc_map_logw_append(tid_t);

#endif
