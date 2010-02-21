#ifndef XOREECEOBEKENGIEQUID
#define XOREECEOBEKENGIEQUID

#include "Types.h"
#include "LogWrite.h"

// from tos/interfaces/LogWrite.nc

// emulation of nesc wire statements
// the returned handle must be passed to all commands
void* logw_wire(const char* file);

/**
* Append data to a given volume.
* 
* @param 'void* COUNT(len) buf' buffer to write data from.
* @param len number of bytes to write.
* @param res_len number of bytes actually written (valid even in case of error)
* @param recordsLost true if this append destroyed some old records from
*    the beginning of the log (only possible for circular logs).
* @return 
*   <li>SUCCESS if append was possible.
*   <li>EINVAL if the request is invalid (len too large).
*   <li>EBUSY if a request is already being processed.
*   <li>ESIZE if the (linear) log us full.
*   <li>FAIL for other errors.
*/
error_t logw_append(void* handle, void* buf, storage_len_t len, storage_len_t* res_len, bool* recordsLost);

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
*   <li>SUCCESS if the log was erased.
*   <li>EBUSY if a request is already being processed.
*   <li>FAIL otherwise.
*/
error_t logw_erase(void* handle);

/**
* Ensure all writes are present on flash, and that failure in subsequent
* writes cannot cause loss of earlier writes. 
*
* @return 
*   <li>SUCCESS if the log was synchronised.
*   <li>EBUSY if a request is already being processed.
*   <li>FAIL otherwise.
*/
error_t logw_sync(void* handle);

#endif
