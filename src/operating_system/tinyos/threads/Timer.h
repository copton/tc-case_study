#ifndef BOHSHOHKOXUMEETACHAI
#define BOHSHOHKOXUMEETACHAI

// from tos/lib/timer/Timer.nc
// a unit is a millisecond

#include "Types.h"

/**
 * sleep until a future point in time.
 *
 */
void timer_sleep(uint64_t until);

/**
* Return the current time.
* @return Current time.
*/
uint64_t timer_getNow();

#endif
