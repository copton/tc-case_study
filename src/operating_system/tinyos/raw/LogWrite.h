#ifndef EIXAHZUOWAXUINGIEPHO
#define EIXAHZUOWAXUINGIEPHO

#include "Types.h"
#include "Log.h"

// from tos/interfaces/LogWrite.nc

typedef struct {
    /**
    * Signals the completion of an append operation. However, data is not
    * guaranteed to survive a power-cycle unless a commit operation has
    * been completed.
    *
    * @param 'void* COUNT(len) buf' buffer that written data was read from.
    * @param len number of bytes actually written (valid even in case of error)
    * @param records_lost true if this append destroyed some old records from
    *   the beginning of the log (only possible for circular logs).
    * @param error SUCCESS if append was possible, ESIZE if the (linear) log
    *    is full and FAIL for other errors.
    */
    void (*appendDone)(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error);

    /**
    * Signals the completion of an erase operation.
    *
    * @param error SUCCESS if the log was erased, FAIL otherwise.
    */
    void (*eraseDone)(void* handle, error_t error);

    /**
    * Signals the successful or unsuccessful completion of a sync operation. 
    *
    * @param error SUCCESS if the log was synchronised, FAIL otherwise.
    */
    void (*syncDone)(void* handle, error_t error);
} logw_Callback;

// emulation of nesc wire statements
// the returned handle must be passed to all commands and is passed to all events
void* logw_wire(logw_Callback* callback, const char* file);

/**
* Append data to a given volume. On SUCCESS, the <code>appendDone</code> 
* event will signal completion of the operation.
* 
* @param 'void* COUNT(len) buf' buffer to write data from.
* @param len number of bytes to write.
* @return 
*   <li>SUCCESS if the request was accepted, 
*   <li>EINVAL if the request is invalid (len too large).
*   <li>EBUSY if a request is already being processed.
*/
error_t logw_append(void* handle, void* buf, storage_len_t len);

/**
* Return a "cookie" representing the current append offset within the
* log. This cookie can be used in a subsequent seek operation (see
* <code>LogRead</code> to start reading from this place in the log (if
* it hasn't been overwritten).
*
* The current write position is not known before the first read, append,
* seek, erase or sync.
*
* @return Cookie representing current offset. 
*/
storage_cookie_t logw_currentOffset(void* handle);

/**
* Initiate an erase operation. On SUCCESS, the
* <code>eraseDone</code> event will signal completion of the
* operation.
*
* @return 
*   <li>SUCCESS if the request was accepted, 
*   <li>EBUSY if a request is already being processed.
*/
error_t logw_erase(void* handle);

/**
* Ensure all writes are present on flash, and that failure in subsequent
* writes cannot cause loss of earlier writes. On SUCCES, the 
* <code>commitDone</code> event will signal completion of the operation.
*
* @return 
*   <li>SUCCESS if the request was accepted, 
*   <li>EBUSY if a request is already being processed.
*/
error_t logw_sync(void* handle);

#endif
