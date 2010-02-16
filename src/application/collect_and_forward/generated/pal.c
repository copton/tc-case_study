#include "threads.h"
#include <assert.h>

#include "LogRead.h"

tc_logr_wire_t tc_state_logr_wire[1];
unsigned tc_map_logr_wire()
{
	assert (tc_tid == TC_TID_SEND);
	return 0;
}

tc_logr_read_t tc_state_logr_read[1];
unsigned tc_map_logr_read()
{
	assert (tc_tid == TC_TID_SEND);
	return 0;
}
#include "LogWrite.h"

tc_logw_wire_t tc_state_logw_wire[2];
unsigned tc_map_logw_wire()
{
	assert (tc_tid == TC_TID_COLLECT || tc_tid == TC_TID_RECEIVE);
	return tc_tid;
}

tc_logw_append_t tc_state_logw_append[2];
unsigned tc_map_logw_append()
{
	assert (tc_tid == TC_TID_COLLECT || tc_tid == TC_TID_RECEIVE);
	return tc_tid;
}
#include "Receive.h"

tc_receive_wire_t tc_state_receive_wire[1];
unsigned tc_map_receive_wire()
{
	assert (tc_tid == TC_TID_RECEIVE);
    return 0;
}

tc_receive_receive_t tc_state_receive_receive[1];
unsigned tc_map_receive_receive()
{
	assert (tc_tid == TC_TID_RECEIVE);
    return 0;
}
#include "Send.h"

tc_send_wire_t tc_state_send_wire[1];
unsigned tc_map_send_wire()
{
	assert (tc_tid == TC_TID_SEND);
    return 0;
}

tc_send_send_t tc_state_send_send[1];
unsigned tc_map_send_send()
{
	assert (tc_tid == TC_TID_SEND);
    return 0;
}
#include "Sensor.h"

tc_sensor_wire_t tc_state_sensor_wire[1];
unsigned tc_map_sensor_wire()
{
	assert (tc_tid == TC_TID_COLLECT);
	return 0;
}

tc_sensor_read_t tc_sensor_logr_read[1];
unsigned tc_map_sensor_read()
{
	assert (tc_tid == TC_TID_COLLECT);
	return 0;
}
#include "Timer.h"

tc_timer_sleep_t tc_state_timer_sleep[2];
unsigned tc_map_timer_sleep()
{
	assert (tc_tid == TC_TID_COLLECT || tc_tid == TC_TID_SEND);
	switch (tc_tid) {
		case TC_TID_COLLECT: return 0;
		case TC_TID_SEND: return 1;
	}

	return -1;
}
