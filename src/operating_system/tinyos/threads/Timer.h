#ifndef BOHSHOHKOXUMEETACHAI
#define BOHSHOHKOXUMEETACHAI

// from tos/lib/timer/Timer.nc
// a unit is a millisecond

#include "compiler/tc.h"
#include "Types.h"

// emulation of nesc wire statements
// the returned handle must be passed to all commands
void* timer_wire();

/**
 * sleep until a future point in time.
 *
 */
TC_BLOCKING error_t timer_sleep(void* handle, uint32_t until);

/**
* Return the current time.
* @return Current time.
*/
uint32_t timer_getNow(void* handle);

#endif
