#ifndef PHOHSHOONAEGEEPOHFEE
#define PHOHSHOONAEGEEPOHFEE

// a unit is a millisecond

#include "raw/Types.h"
#include "compiler/ec.h"

//void timer_sleep(uint64_t until);
typedef struct {
    ec_continuation_t ec_continuation;
} ec_struct_timer_sleep;
void ec_pal_timer_sleep(uint64_t until);
extern ec_struct_timer_sleep ec_state_timer_sleep[];
unsigned ec_map_timer_sleep();

/**
* Return the current time.
* @return Current time.
*/
uint64_t ec_pal_timer_getNow();

#endif
