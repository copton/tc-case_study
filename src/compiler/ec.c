#include "ec.h"
#include <stdarg.h>
#include "infra/debug.h"

static ec_tid_t the_tid = 0;

ec_tid_t ec_tid()
{
    return the_tid;
}

void ec_set_tid(ec_tid_t tid)
{
    DEBUGOUT("%d: setting tid to %d", the_tid, tid);
    the_tid = tid;
}

void EC_RUN_THREAD(void* stack)
{
    ec_set_tid(ec_tid() + 1);
	DEBUGOUT("running thread %d", ec_tid());
    ec_continuation_t cont = {0,stack};
    ec_events(cont);
}
