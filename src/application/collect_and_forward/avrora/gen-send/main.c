#include "event-based/send.c"

int main()
{
	send_init("", "", "", 0);
	fired(timer_handle);
	readDone(logr_handle_1, read_buffer, 12, SUCCESS);
	readDone(logr_handle_2, read_buffer, 12, SUCCESS);
	sendDone(send_handle, &message, SUCCESS);
	return 0;	
}
