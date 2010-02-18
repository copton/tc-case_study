#include "ec.h"
#include <stdarg.h>

ec_tid_t ec_tid;

static void run_thread(ec_continuation_t run)
{
    static ec_tid_t tid = 0;
    ec_tid = tid;
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
