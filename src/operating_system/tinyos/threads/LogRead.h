#ifndef OOFOOYOHIEPINGETOGOO
#define OOFOOYOHIEPINGETOGOO

#include "Types.h"
#include "Log.h"

// from tos/interfaces/LogRead.nc

// emulation of nesc wire statements
// the returned handle must be passed to all commands
void* logr_wire(const char* file);

/**
* Do a read operation from the current position within a given log
* volume. 
* 
* @param 'void* COUNT(len) buf' buffer to place read data.
* @param len number of bytes to read.
* @param res_len number of bytes actually read.
* @return
*   <li>SUCCESS if read was possible.
*   <li>EBUSY if a request is already being processed.
*   <li>FAIL otherwise.
*/
error_t logr_read(void* handle, void* buf, storage_len_t len, storage_len_t* res_len);

/**
* Return a "cookie" representing the current read offset within the
* log. This cookie can be used in a subsequent seek operation to
* return to the same place in the log (if it hasn't been overwritten).
*
* @return Cookie representing current offset. 
*   <code>SEEK_BEGINNING</code> will be returned if:<ul>
*   <li> a write in a circular log overwrote the previous read position
*   <li> seek was passed a cookie representing a position before the
*        current beginning of a circular log
*   </ul>
*   Note that <code>SEEK_BEGINNING</code> can also be returned at
*   other times (just after erasing a log, etc).
*/
storage_cookie_t logr_currentOffset(void* handle);

/**
* Set the read position in the log, using a cookie returned by the
* <code>currentOffset</code> commands of <code>LogRead</code> or
* <code>LogWrite</code>, or the special value <code>SEEK_BEGINNING</code>.
*
* If the specified position has been overwritten, the read position
* will be set to the beginning of the log.
*
* @return 
*     <li>SUCCESS if the seek was succesful.
*     <li>EBUSY if a request is already being processed.
*     <li>EINVAL if the cookie was invalid.
*     <li>FAIL for other errors.
*/
error_t logr_seek(void* handle, storage_cookie_t offset);

/**
* Report approximate log capacity in bytes. Note that use of
* <code>sync</code>, failures and general overhead may reduce the number
* of bytes available to the log. 
*
* @return Volume size.
*/
storage_len_t logr_getSize(void* handle);

#endif
