#include "send.h"
#include "receive.h"
#include "collect.h"
#include <assert.h>
#include "infra/types.h"
#include "config.h"

static void run_send()
{
	send_run(fn_send, fn_flash_receive_source, fn_flash_collect_source, dt_send);
	assert (FALSE);
}

static void run_receive()
{
	receive_run(fn_receive, fn_flash_receive_sink);
	assert (FALSE);
}

static void run_collect()
{
	collect_run(fn_collect, fn_flash_collect_sink, dt_collect);
	assert (FALSE);
}

int main()
{
	RUN_THREADS(run_send, run_receive, run_collect);
	assert (FALSE);

	return 0;
}
