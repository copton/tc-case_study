#ifndef OHYOOMIENAEKIEBUIGOO
#define OHYOOMIENAEKIEBUIGOO

#include "Types.h"
#include "LogTypes.h"

// from tos/interfaces/LogRead.nc


typedef struct {
  /**
   * Signals the completion of a read operation. The current read position is
   * advanced by <code>len</code> bytes.
   *
   * @param addr starting address of read.
   * @param 'void* COUNT(len) buf' buffer where read data was placed.
   * @param len number of bytes read - this may be less than requested
   *    (even equal to 0) if the end of the log was reached
   * @param error SUCCESS if read was possible, FAIL otherwise
   */
  void (*readDone)(void* handle, void* buf, storage_len_t len, error_t error);

  /**
   * Report success of seek operation. If <code>SUCCESS</code> is returned,
   * the read position has been changed as requested. If other values are
   * returned, the read position is undefined.
   *
   * @param error SUCCESS if the seek was succesful, EINVAL if the cookie
   *   was invalid and FAIL for other errors.
   */
  void (*seekDone)(void* handle, error_t error);
} logr_Callback;

// emulation of nesc wire statements
// the returned handle must be passed to all commands and is passed to all events
void* logr_wire(logr_Callback* callback, const char* file);

/**
* Initiate a read operation from the current position within a given log
* volume. On SUCCESS, the <code>readDone</code> event will signal
* completion of the operation.
* 
* @param 'void* COUNT(len) buf' buffer to place read data.
* @param len number of bytes to read.
* @return 
*   <li>SUCCESS if the request was accepted, 
*   <li>EBUSY if a request is already being processed.
*/
error_t logr_read(void* handle, void* buf, storage_len_t len);

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
*   <li>SUCCESS if the request was accepted, 
*   <li>EBUSY if a request is already being processed.
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
