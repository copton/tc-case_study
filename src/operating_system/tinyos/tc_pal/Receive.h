#ifndef WOGEKEEXOFIESOKAIKEI
#define WOGEKEEXOFIESOKAIKEI

#include "raw/Types.h"
#include "raw/Net.h"
#include "tc.h"

void* pal_receive_wire(const char* channel);

//void receive_receive(void* handle, net_message_t** msg, void** payload, uint8_t* len);
typedef struct {
    tc_continuation_t tc_continuation;
    net_message_t** msg;
    void** payload;
    uint8_t* len;
} tc_struct_receive_receive;
void tc_pal_receive_receive(void* handle);
extern tc_struct_receive_receive tc_state_receive_receive[];
unsigned tc_map_receive_receive();

#endif
