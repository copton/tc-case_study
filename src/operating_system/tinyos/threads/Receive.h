#ifndef AFAECHOHSIEVIJEEWEVA
#define AFAECHOHSIEVIJEEWEVA

// from tos/interfaces/Receive.nc

#include "compiler/tc.h"
#include "Types.h"
#include "NetTypes.h"

// emulation of nesc wire statements
// the returned handle must be passed to all commands
void* receive_wire(const char* channel);

/**
* Receive a packet buffer
*
* @param  'net_message_t* ONE msg'        the receied packet
* @param  'void* COUNT(len) payload'  a pointer to the packet's payload
* @param  len      the length of the data region pointed to by payload
*                  received packet.
* @return 
*   <li>SUCCESS if the receive() was successful
*   <li>EBUSY if a request is already being processed.
*/
TC_BLOCKING error_t receive_receive(void* handle, net_message_t* msg, void** payload, uint8_t* len);

#endif
