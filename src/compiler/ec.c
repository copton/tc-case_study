#include "ec.h"
#include <stdarg.h>
#include "infra/debug.h"

static ec_tid_t tid;

ec_tid_t ec_tid()
{
    return tid;
}

void ec_set_tid(ec_tid_t t)
{
    DEBUGOUT("%d: setting tid to %d", tid, t);
    tid = t;
}

void ec_set_tid(ec_tid_t tid);


static void run_thread(ec_continuation_t run)
{
    static ec_tid_t tid = 0;
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
