#include "event-based/receive.c"

int main()
{
	receive_init("", "");
	receive(receive_handle, 0, 0, 2 * sizeof(uint32_t));
	appendDone(logw_handle, 0, cur_len, 0, SUCCESS);
	return 0;	
}
