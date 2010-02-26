#include "mockup/Queue.h"
#include "mockup/Os.h"
#include "event-based/collect.h"

int main()
{
	os_init();
 	collect_init("", "", 0);
	q_next();
/*	
	q_next();
	q_next();
*/
	return 0;	
}
