#include "mockup/Queue.h"
#include "mockup/Os.h"
#include "mockup/ReceiveInput.h"
#include "event-based/collect.h"
#include "event-based/receive.h"
#include "event-based/send.h"

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
