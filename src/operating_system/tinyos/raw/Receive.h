#ifndef TOOSHIETHEEGEITEICIR
#define TOOSHIETHEEGEITEICIR

// from tos/interfaces/Receive.nc

#include "Types.h"
#include "Net.h"

typedef struct {
    /**
    * Receive a packet buffer, returning a buffer for the signaling
    * component to use for the next reception. The return value
    * can be the same as <tt>msg</tt>, as long as the handling
    * component copies out the data it needs.
    *
    * <b>Note</b> that misuse of this interface is one of the most
    * common bugs in TinyOS code. For example, if a component both calls a
    * send on the passed message and returns it, then it is possible
    * the buffer will be reused before the send occurs, overwriting
    * the component's data. This would cause the mote to possibly
    * instead send a packet it most recently received.
    *
    * @param  'net_message_t* ONE msg'        the receied packet
    * @param  'void* COUNT(len) payload'  a pointer to the packet's payload
    * @param  len      the length of the data region pointed to by payload
    * @return 'net_message_t* ONE'              a packet buffer for the stack to use for the next
    *                  received packet.
    */
    net_message_t* (*receive)(void* handle, net_message_t* msg, void* payload, uint8_t len);
} receive_Callback;

// emulation of nesc wire statements
// the returned handle must be passed to all commands and is passed to all events
void* receive_wire(receive_Callback* callback, const char* channel);

#endif
