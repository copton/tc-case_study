#ifndef IULIETATEIWAEVAEJIEY
#define IULIETATEIWAEVAEJIEY

// from tos/lib/timer/Timer.nc
// a unit is a millisecond

#include "infra/types.h"

typedef struct {
    /**
    * Signaled when the timer expires (one-shot) or repeats (periodic).
    */
    void (*fired)(void* handle);
} timer_Callback;

// emulation of nesc wire statements
// the returned handle must be passed to all commands and is passed to all events
void* timer_wire(timer_Callback*);

/**
* Set a periodic timer to repeat every dt time units. Replaces any
* current timer settings. Equivalent to startPeriodicAt(getNow(),
* dt). The <code>fired</code> will be signaled every dt units (first
* event in dt units).
*
* @param dt Time until the timer fires.
*/
void timer_startPeriodic(void* handle, uint32_t dt);

/**
* Set a single-short timer to some time units in the future. Replaces
* any current timer settings. Equivalent to startOneShotAt(getNow(),
* dt). The <code>fired</code> will be signaled when the timer expires.
*
* @param dt Time until the timer fires.
*/
void timer_startOneShot(void* handle, uint32_t dt);

/**
* Cancel a timer.
*/
void timer_stop(void* handle);

// extended interface
/**
* Check if timer is running. Periodic timers run until stopped or
* replaced, one-shot timers run until their deadline expires.
*
* @return TRUE if the timer is still running.
*/
bool timer_isRunning(void* handle);

/**
* Check if this is a one-shot timer.
* @return TRUE for one-shot timers, FALSE for periodic timers.
*/
bool timer_isOneShot(void* handle);

/**
* Set a periodic timer to repeat every dt time units. Replaces any
* current timer settings. The <code>fired</code> will be signaled every
* dt units (first event at t0+dt units). Periodic timers set in the past
* will get a bunch of events in succession, until the timer "catches up".
*
* <p>Because the current time may wrap around, it is possible to use
* values of t0 greater than the <code>getNow</code>'s result. These
* values represent times in the past, i.e., the time at which getNow()
* would last of returned that value.
*
* @param t0 Base time for timer.
* @param dt Time until the timer fires.
*/
void timer_startPeriodicAt(void* handle, uint32_t t0, uint32_t dt);

/**
* Set a single-short timer to time t0+dt. Replaces any current timer
* settings. The <code>fired</code> will be signaled when the timer
* expires. Timers set in the past will fire "soon".
*
* <p>Because the current time may wrap around, it is possible to use
* values of t0 greater than the <code>getNow</code>'s result. These
* values represent times in the past, i.e., the time at which getNow()
* would last of returned that value.
*
* @param t0 Base time for timer.
* @param dt Time until the timer fires.
*/
void timer_startOneShotAt(void* handle, uint32_t t0, uint32_t dt);


/**
* Return the current time.
* @return Current time.
*/
uint32_t timer_getNow(void* handle);

/**
* Return the time anchor for the previously started timer or the time of
* the previous event for periodic timers. The next fired event will occur
* at gett0() + getdt().
* @return Timer's base time.
*/
uint32_t timer_gett0(void* handle);

/**
* Return the delay or period for the previously started timer. The next
* fired event will occur at gett0() + getdt().
* @return Timer's interval.
*/
uint32_t timer_getdt(void* handle);

#endif
