#ifndef OHPOODIEMIEPHEECEIVU
#define OHPOODIEMIEPHEECEIVU

#include "raw/Types.h"
#include "raw/Net.h"
#include "tc.h"

//void* send_wire(const char* channel);
typedef struct {
    tc_continuation_t tc_continuation;
    void* tc_result;
} tc_send_wire_t;
void tc_pal_send_wire(const char* channel);
extern tc_send_wire_t tc_state_send_wire[];
unsigned tc_map_send_wire();


//error_t send_send(void* handle, net_message_t* msg, uint8_t len);
typedef struct  {
    tc_continuation_t tc_continuation;
    error_t tc_result;
    net_message_t* msg;
} tc_send_send_t;
void tc_pal_send_send(void* handle, uint8_t len);
extern tc_send_send_t tc_state_send_send[];
unsigned tc_map_send_send();

#endif
