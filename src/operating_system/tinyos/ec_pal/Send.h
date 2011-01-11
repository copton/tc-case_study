#ifndef OHPOODIEMIEPHEECEIVU
#define OHPOODIEMIEPHEECEIVU

#include "Types.h"
#include "NetTypes.h"
#include "compiler/ec.h"

void* pal_send_wire(const char* channel);

typedef struct  {
    ec_continuation_t ec_cont;
    // signature
    error_t ec_result;
    net_message_t* msg;
} ec_stack_send_send;

void ec_pal_send_send(ec_stack_send_send* stack, void* handle, uint8_t len);

#endif
