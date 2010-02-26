#include "mockup/Queue.h"
#include "mockup/Os.h"
#include "mockup/ReceiveInput.h"
#include "generated/threads.h"
#include "compiler/ec.h"

int main()
{
	os_init();

	ec_set_tid(EC_TID_COLLECT);
	run_collect();
	q_next();
	q_next();
	q_next();

	ec_set_tid(EC_TID_RECEIVE);
 	run_receive();
	receive_input();	
	q_next();
	q_next();

	ec_set_tid(EC_TID_SEND);
 	run_send();
	q_next();
	q_next();
	q_next();
	q_next();

	return 0;	
}
