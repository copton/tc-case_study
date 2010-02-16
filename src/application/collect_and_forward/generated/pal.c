#include "threads.h"
#include <assert.h>

#include "LogWrite.h"
#include "LogRead.h"
#include "Send.h"
#include "Receive.h"
#include "Timer.h"

tc_struct_logr_read tc_state_logr_read[1];
unsigned tc_map_logr_read()
{
	assert (tc_tid == TC_TID_SEND);
	return 0;
}
#include "LogWrite.h"

tc_struct_logw_append tc_state_logw_append[2];
unsigned tc_map_logw_append()
{
	assert (tc_tid == TC_TID_COLLECT || tc_tid == TC_TID_RECEIVE);
	return tc_tid;
}
#include "Receive.h"

tc_struct_receive_receive tc_state_receive_receive[1];
unsigned tc_map_receive_receive()
{
	assert (tc_tid == TC_TID_RECEIVE);
    return 0;
}
#include "Send.h"

tc_struct_send_send tc_state_send_send[1];
unsigned tc_map_send_send()
{
	assert (tc_tid == TC_TID_SEND);
    return 0;
}
#include "Sensor.h"

tc_struct_sensor_read tc_state_sensor_read[1];
unsigned tc_map_sensor_read()
{
	assert (tc_tid == TC_TID_COLLECT);
	return 0;
}
#include "Timer.h"

tc_struct_timer_sleep tc_state_timer_sleep[2];
unsigned tc_map_timer_sleep()
{
	assert (tc_tid == TC_TID_COLLECT || tc_tid == TC_TID_SEND);
	switch (tc_tid) {
		case TC_TID_COLLECT: return 0;
		case TC_TID_SEND: return 1;
	}

	return -1;
}
