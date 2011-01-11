#ifndef WOGEKEEXOFIESOKAIKEI
#define WOGEKEEXOFIESOKAIKEI

#include "Types.h"
#include "NetTypes.h"
#include "compiler/ec.h"

void* pal_receive_wire(const char* channel);

typedef struct {
    ec_continuation_t ec_cont;
    // signature
    error_t ec_result;
    net_message_t* msg;
    void** payload;
    uint8_t* len;
} ec_stack_receive_receive;

void ec_pal_receive_receive(ec_stack_receive_receive* stack, void* handle);

#endif
