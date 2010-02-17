#include "threads.h"
#include <assert.h>

#include "LogWrite.h"
#include "LogRead.h"
#include "Send.h"
#include "Receive.h"
#include "Timer.h"

ec_struct_logr_read ec_state_logr_read[1];
unsigned ec_map_logr_read()
{
	assert (ec_tid == EC_TID_SEND);
	return 0;
}
#include "LogWrite.h"

ec_struct_logw_append ec_state_logw_append[2];
unsigned ec_map_logw_append()
{
	assert (ec_tid == EC_TID_COLLECT || ec_tid == EC_TID_RECEIVE);
	return ec_tid;
}
#include "Receive.h"

ec_struct_receive_receive ec_state_receive_receive[1];
unsigned ec_map_receive_receive()
{
	assert (ec_tid == EC_TID_RECEIVE);
    return 0;
}
#include "Send.h"

ec_struct_send_send ec_state_send_send[1];
unsigned ec_map_send_send()
{
	assert (ec_tid == EC_TID_SEND);
    return 0;
}
#include "Sensor.h"

ec_struct_sensor_read ec_state_sensor_read[1];
unsigned ec_map_sensor_read()
{
	assert (ec_tid == EC_TID_COLLECT);
	return 0;
}
#include "Timer.h"

ec_struct_timer_sleep ec_state_timer_sleep[2];
unsigned ec_map_timer_sleep()
{
	assert (ec_tid == EC_TID_COLLECT || ec_tid == EC_TID_SEND);
	switch (ec_tid) {
		case EC_TID_COLLECT: return 0;
		case EC_TID_SEND: return 1;
	}

	return -1;
}
