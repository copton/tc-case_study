#ifndef TOOSHIETHEEGEITEICIR
#define TOOSHIETHEEGEITEICIR

// from tos/interfaces/Receive.nc
// from tos/interfaces/Send.nc

#include "types.h"


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

    net_message_t* (*receive)(net_message_t* msg, void* payload, uint8_t len);

    /** 
    * Signaled in response to an accepted send request. <tt>msg</tt>
    * is the sent buffer, and <tt>error</tt> indicates whether the
    * send was succesful, and if not, the cause of the failure.
    * 
    * @param 'net_message_t* ONE msg'   the message which was requested to send
    * @param error SUCCESS if it was transmitted successfully, FAIL if
    *              it was not, ECANCEL if it was cancelled via <tt>cancel</tt>
    */ 
    void (*sendDone)(net_message_t* msg, error_t error);

} net_Callback;


/** 
* Send a packet with a data payload of <tt>len</tt>. To determine
* the maximum available size, use the Packet interface of the
* component providing Send. If send returns SUCCESS, then the
* component will signal the sendDone event in the future; if send
* returns an error, it will not signal sendDone.  Note that a
* component may accept a send request which it later finds it
* cannot satisfy; in this case, it will signal sendDone with an
* appropriate error code.
*
* @param   'net_message_t* ONE msg'     the packet to send
* @param   len     the length of the packet payload
* @return          SUCCESS if the request was accepted and will issue
*                  a sendDone event, EBUSY if the component cannot accept
*                  the request now but will be able to later, FAIL
*                  if the stack is in a state that cannot accept requests
*                  (e.g., it's off).
*/ 
error_t net_send(net_message_t* msg, uint8_t len);

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
error_t net_cancel(net_message_t* msg);

/**
* Return the maximum payload length that this communication layer
* can provide. This command behaves identically to
* <tt>Packet.maxPayloadLength</tt> and is included in this
* interface as a convenience.
*
* @return  the maximum payload length
*/

uint8_t net_maxPayloadLength();


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
void* net_getPayload(net_message_t* msg, uint8_t len);


#endif
