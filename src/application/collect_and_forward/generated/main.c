#include "compiler/ec.h"
#include "threads.h"
#include "Pal.h"
#include "infra/types.h"
#include "infra/debug.h"

int main()
{
	pal_init();
    RUN_THREAD(run_collect);
    RUN_THREAD(run_receive);
    RUN_THREAD(run_send);
	pal_run();
    assert (false);

    return 0;
}
