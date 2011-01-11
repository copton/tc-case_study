#include "send.h"
#include "receive.h"
#include "collect.h"
#include "infra/types.h"
#include "infra/debug.h"
#include "config.h"
#include "compiler/tc.h"

TC_RUN_THREAD run_send()
{
	send_run(fn_send, fn_flash_receive_source, fn_flash_collect_source, dt_send);
	assert (false);
	return NULL;
}

TC_RUN_THREAD run_receive()
{
	receive_run(fn_receive, fn_flash_receive_sink);
	assert (false);
	return NULL;
}

TC_RUN_THREAD run_collect(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	collect_run(fn_collect, fn_flash_collect_sink, dt_collect);
	assert (false);
	return NULL;
}
