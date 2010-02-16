#ifndef AFAECHOHSIEVIJEEWEVA
#define AFAECHOHSIEVIJEEWEVA

#include "raw/Types.h"
#include "raw/Net.h"
#include "tc.h"

//void* receive_wire(const char* channel);
typedef struct {
    tc_continuation_t tc_continuation;
    void* tc_result;
} tc_receive_wire_t;
void tc_pal_receive_wire(const char* channel);
extern tc_receive_wire_t tc_state_receive_wire[];
unsigned tc_map_receive_wire();


//void receive_receive(void* handle, net_message_t** msg, void** payload, uint8_t* len);
typedef struct {
    tc_continuation_t tc_continuation;
    net_message_t** msg;
    void** payload;
    uint8_t* len;
} tc_receive_receive_t;
void tc_pal_receive_receive(void* handle);
extern tc_receive_receive_t tc_state_receive_receive[];
unsigned tc_map_receive_receive();

#endif
