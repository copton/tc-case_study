#include "mockup/Queue.h"
#include "mockup/Os.h"
#include "mockup/ReceiveInput.h"
#include "compiler/ec.h"
#include "infra/debug.h"
#include "generated/tstack.h"

ec_stack_14 tstack_1;
ec_stack_10 tstack_2;
ec_stack_8 tstack_3;

int main()
{
	ec_continuation_t cont = {NULL, NULL};

	os_init();

	DEBUGOUT("main: running receive");
	ec_set_tid(1);
	cont.stack = &tstack_1;
 	ec_events(cont);
	receive_input();	
	q_next();
	q_next();

	DEBUGOUT("main: running collect");
	ec_set_tid(2);
	cont.stack = &tstack_2;
	q_next();
	q_next();
	q_next();


	DEBUGOUT("main: running send");
	ec_set_tid(3);
	cont.stack = &tstack_3;
 	ec_events(cont);
	q_next();
	q_next();
	q_next();
	q_next();

	return 0;	
}
