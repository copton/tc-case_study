#ifndef RAELOHNEIQUAXALIGAID
#define RAELOHNEIQUAXALIGAID

#include "raw/Types.h"
#include "raw/Log.h"
#include "tc.h"

// void* logr_wire(tid_t tid, const char* file);
typedef struct {
    tc_continuation_t tc_continuation;
    void* tc_result;
} tc_logr_wire_t;
extern tc_logr_wire_t tc_state_logr_wire[];
unsigned tc_map_logr_wire(tid_t);
void tc_pal_logr_wire(tid_t, const char* filename);

//error_t logr_read(void* handle, void* buf, storage_len_t len, storage_len_t* res_len);
typedef struct {
    tc_continuation_t tc_continuation;
    void* buf;
    storage_len_t* res_len;
    error_t tc_result;    
} tc_logr_read_t;
extern tc_logr_read_t tc_state_logr_read[];
void tc_pal_logr_read(tid_t tid, void* handle, storage_len_t len);
unsigned tc_map_logr_read(tid_t);

#endif
