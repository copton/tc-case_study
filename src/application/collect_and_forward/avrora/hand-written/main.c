#include "mockup/Queue.h"
#include "mockup/Os.h"
#include "mockup/ReceiveInput.h"
#include "hand-written/collect.h"
#include "hand-written/receive.h"
#include "hand-written/send.h"

int main()
{
	os_init();

 	collect_init("", "", 0);
	q_next();
	q_next();
	q_next();

 	receive_init("", "");
	receive_input();	
	q_next();
	q_next();

 	send_init("", "", "", 0);
	q_next();
	q_next();
	q_next();
	q_next();

	return 0;	
}
