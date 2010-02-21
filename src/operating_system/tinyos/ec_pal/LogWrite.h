#ifndef OOPHEIWOHXAISEFOOTOO
#define OOPHEIWOHXAISEFOOTOO

#include "Types.h"
#include "LogTypes.h"
#include "compiler/ec.h"

void* pal_logw_wire(const char* file);

//error_t logw_append(void* handle, void* buf, storage_len_t len, storage_len_t* res_len, bool* recordsLost);
typedef struct {
    ec_continuation_t ec_continuation;
    
    //signature
    error_t ec_result;    
    void* buf;
    storage_len_t* res_len;
    bool* recordsLost;
} ec_struct_logw_append;
void ec_pal_logw_append(void* handle, storage_len_t len);
extern ec_struct_logw_append ec_state_logw_append[];
ec_struct_logw_append* ec_map_logw_append();

#endif
