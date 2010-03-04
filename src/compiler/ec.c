#include "ec.h"
#include <stdarg.h>
#include "infra/debug.h"

ec_tid_t the_tid = ec_invalid_tid;

/*
ec_tid_t ec_tid()
{
    return the_tid;
}

void ec_set_tid(ec_tid_t tid)
{
    DEBUGOUT("%d: setting tid to %d", the_tid, tid);
    the_tid = tid;
}
*/

static ec_tid_t tid = 0;

void RUN_THREAD(ec_continuation_t start_function)
{
	DEBUGOUT("running thread %d", tid);
    ec_set_tid(tid);
    start_function();
    tid++;
}
