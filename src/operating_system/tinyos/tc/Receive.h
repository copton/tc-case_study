#ifndef AFAECHOHSIEVIJEEWEVA
#define AFAECHOHSIEVIJEEWEVA

#include "Types.h"
#include "Net.h"

void* receive_wire(const char* channel);

error_t receive_receive(void* handle, net_message_t** msg, void** payload, uint8_t* len);

#endif
