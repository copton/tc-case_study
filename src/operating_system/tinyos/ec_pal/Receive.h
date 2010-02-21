#ifndef WOGEKEEXOFIESOKAIKEI
#define WOGEKEEXOFIESOKAIKEI

#include "Types.h"
#include "NetTypes.h"
#include "compiler/ec.h"

void* pal_receive_wire(const char* channel);

typedef struct {
    ec_continuation_t ec_continuation;
    // signature
    error_t ec_result;
    net_message_t* msg;
    void** payload;
    uint8_t* len;
} ec_struct_receive_receive;
void ec_pal_receive_receive(void* handle);

extern ec_struct_receive_receive ec_state_receive_receive[];
ec_struct_receive_receive* ec_map_receive_receive();

#endif
