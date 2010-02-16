#ifndef OHPOODIEMIEPHEECEIVU
#define OHPOODIEMIEPHEECEIVU

#include "raw/Types.h"
#include "raw/Net.h"
#include "tc.h"

void* pal_send_wire(const char* channel);

//error_t send_send(void* handle, net_message_t* msg, uint8_t len);
typedef struct  {
    tc_continuation_t tc_continuation;
    error_t tc_result;
    net_message_t* msg;
} tc_struct_send_send;
void tc_pal_send_send(void* handle, uint8_t len);
extern tc_struct_send_send tc_state_send_send[];
unsigned tc_map_send_send();

#endif
