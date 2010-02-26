#include "compiler/ec.h"
#include "threads.h"
#include "Pal.h"
#include "infra/types.h"
#include "infra/debug.h"

int main()
{
	pal_init();
    RUN_THREADS(EC_NUMBEROF_THREADS, run_collect, run_receive, run_send);
	pal_run();
    assert (false);

    return 0;
}
