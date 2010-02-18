#include "ec.h"
#include <stdarg.h>
#include "infra/debug.h"

static ec_tid_t the_tid = ec_invalid_tid;

ec_tid_t ec_tid()
{
    return the_tid;
}

void ec_set_tid(ec_tid_t tid)
{
    DEBUGOUT("%d: setting tid to %d", the_tid, tid);
    the_tid = tid;
}

void ec_set_tid(ec_tid_t tid);


static void run_thread(ec_continuation_t run)
{
    static ec_tid_t tid = 0;
	DEBUGOUT("running thread %d", tid);
    ec_set_tid(tid);
    run();
    tid++;
}

void RUN_THREADS(int numberof_threads, ...)
{
    va_list ap;
    va_start(ap, numberof_threads);
    int i;
    for (i=0; i<numberof_threads; i++) {
        ec_continuation_t next_thread = va_arg(ap, ec_continuation_t);
        run_thread(next_thread);
    }
}
