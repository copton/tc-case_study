#include "event-based/collect.c"

int main()
{
	collect_init("", "", 0);
	fired(timer_handle);
	readDone(logw_handle, SUCCESS, 23);
	appendDone(logw_handle, 0, sizeof(sensor_val_t), 0, SUCCESS);
	return 0;	
}
