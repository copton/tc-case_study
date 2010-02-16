#ifndef PHOHSHOONAEGEEPOHFEE
#define PHOHSHOONAEGEEPOHFEE

// a unit is a millisecond

#include "raw/Types.h"
#include "tc.h"

//void timer_sleep(uint64_t until);
typedef struct {
    tc_continuation_t tc_continuation;
} tc_timer_sleep_t;
void tc_pal_timer_sleep(uint64_t until);
extern tc_timer_sleep_t tc_state_timer_sleep[];
unsigned tc_map_timer_sleep();

/**
* Return the current time.
* @return Current time.
*/
uint64_t tc_pal_timer_getNow();

#endif
