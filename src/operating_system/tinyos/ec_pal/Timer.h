#ifndef PHOHSHOONAEGEEPOHFEE
#define PHOHSHOONAEGEEPOHFEE

// a unit is a millisecond

#include "Types.h"
#include "compiler/ec.h"

//void timer_sleep(uint32_t until);
typedef struct {
    ec_continuation_t ec_cont;
// local
    void (*fired)(void*);
} ec_stack_timer_sleep;
void ec_pal_timer_sleep(ec_stack_timer_sleep* stack, void* handle, uint32_t until);

void* pal_timer_wire();

/**
* Return the current time.
* @return Current time.
*/
uint32_t pal_timer_getNow(void* handle);

#endif
