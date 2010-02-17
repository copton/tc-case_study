#ifndef OHPOODIEMIEPHEECEIVU
#define OHPOODIEMIEPHEECEIVU

#include "raw/Types.h"
#include "raw/Net.h"
#include "compiler/ec.h"

void* pal_send_wire(const char* channel);

typedef struct  {
    ec_continuation_t ec_continuation;
    // signature
    error_t ec_result;
    net_message_t* msg;
} ec_struct_send_send;
void ec_pal_send_send(void* handle, uint8_t len);
extern ec_struct_send_send ec_state_send_send[];
unsigned ec_map_send_send();

#endif
