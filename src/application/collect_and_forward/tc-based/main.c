#include "send.h"
#include "receive.h"
#include "collect.h"
#include "infra/types.h"
#include "infra/debug.h"
#include "config.h"
#include "compiler/tc.h"

static void* run_send(void* args)
{
	(void)args;
	send_run(fn_send, fn_flash_receive_source, fn_flash_collect_source, dt_send);
	assert (false);
	return NULL;
}

static void* run_receive(void* args)
{
	(void)args;
	receive_run(fn_receive, fn_flash_receive_sink);
	assert (false);
	return NULL;
}

static void* run_collect(void* args)
{
	(void)args;
	collect_run(fn_collect, fn_flash_collect_sink, dt_collect);
	assert (false);
	return NULL;
}

int main()
{
	RUN_THREAD(run_send);
	RUN_THREAD(run_receive);
	RUN_THREAD(run_collect);

	return 0;
}
