#include "Os.h"
#include "receive.h"
#include "collect.h"
#include "send.h"
#include "infra/infra.h"

#include "config.h"

int main()
{
	infra_init();
    os_init();

    receive_init(fn_receive, fn_flash_receive_sink);
    collect_init(fn_collect, fn_flash_collect_sink, dt_collect); 
    send_init(fn_send, fn_flash_receive_source, fn_flash_collect_source, dt_send);
    os_run();

	return 0;
}
