#include "mockup/Queue.h"
#include "mockup/Os.h"
#include "mockup/ReceiveInput.h"
#include "generated/threads.h"
#include "compiler/ec.h"
#include "infra/debug.h"

int main()
{
	os_init();

	DEBUGOUT("main: running collect");
	ec_set_tid(EC_TID_COLLECT);
	run_collect();
	q_next();
	q_next();
	q_next();

	DEBUGOUT("main: running receive");
	ec_set_tid(EC_TID_RECEIVE);
 	run_receive();
	receive_input();	
	q_next();
	q_next();

	DEBUGOUT("main: running send");
	ec_set_tid(EC_TID_SEND);
 	run_send();
	q_next();
	q_next();
	q_next();
	q_next();

	return 0;	
}
