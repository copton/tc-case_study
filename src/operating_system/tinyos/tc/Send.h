#ifndef TIVAIJEATOHXIEGIWEEK
#define TIVAIJEATOHXIEGIWEEK

// from tos/interfaces/Send.nc

#include "Types.h"
#include "Net.h"

// emulation of nesc wire statements
// the returned handle must be passed to all commands
void* send_wire(const char* channel);

/** 
* Send a packet with a data payload of <tt>len</tt>. To determine
* the maximum available size, use the Packet interface of the
* component providing Send. 
*
* @param   'net_message_t* ONE msg'     the packet to send
* @param   len     the length of the packet payload
* @return          
*   <li>SUCCESS if it was transmitted successfully, 
*   <li>FAIL if it was not.
*   <li>EBUSY if a request is already being processed.
*/ 
error_t send_send(void* handle, net_message_t* msg, uint8_t len);

/**
* Cancel a requested transmission. Returns SUCCESS if the 
* transmission was cancelled properly (not sent in its
* entirety). Note that the component may not know
* if the send was successfully cancelled, if the radio is
* handling much of the logic; in this case, a component
* should be conservative and return an appropriate error code.
*
* @param   'net_message_t* ONE msg'    the packet whose transmission should be cancelled
* @return         SUCCESS if the packet was successfully cancelled, FAIL
*                 otherwise
*/
error_t send_cancel(void* handle, net_message_t* msg);

/**
* Return the maximum payload length that this communication layer
* can provide. This command behaves identically to
* <tt>Packet.maxPayloadLength</tt> and is included in this
* interface as a convenience.
*
* @return  the maximum payload length
*/

uint8_t send_maxPayloadLength(void* handle);

/**
* Return a pointer to a protocol's payload region in a packet which
* at least a certain length.  If the payload region is smaller than
* the len parameter, then getPayload returns NULL. This command
* behaves identicallt to <tt>Packet.getPayload</tt> and is
* included in this interface as a convenience.
*
* @param   'net_message_t* ONE msg'    the packet
* @return  'void* COUNT_NOK(len)'  a pointer to the packet's payload
*/
void* send_getPayload(void* handle, net_message_t* msg, uint8_t len);

#endif
