#include "layout.h"
#include "infra/debug.h"
#include "threads.h"

ec_struct_logr_read* ec_map_logr_read()
{
	assert (ec_tid() == EC_TID_SEND);
    return &ec_states_send.union1.state1.logr_read;
}

ec_struct_logw_append* ec_map_logw_append()
{
	assert (ec_tid() == EC_TID_COLLECT || ec_tid() == EC_TID_RECEIVE);
    switch (ec_tid()) {
        case EC_TID_COLLECT:
            return &ec_states_collect.union1.struct1.logw_append;
        case EC_TID_RECEIVE:
            return &ec_states_receive.union1.struct1.logw_append;
        default:
            return 0;
    }
}

ec_struct_receive_receive* ec_map_receive_receive()
{
    assert (ec_tid() == EC_TID_RECEIVE);
    return &ec_states_receive.union1.receive_receive;
}

ec_struct_send_send* ec_map_send_send()
{
    assert (ec_tid() == EC_TID_SEND);
    return &ec_states_send.union1.state2.send_send;
}

ec_struct_sensor_read* ec_map_sensor_read()
{
    assert (ec_tid() == EC_TID_COLLECT);
    return &ec_states_collect.union1.sensor_read;
}

ec_struct_timer_sleep* ec_map_timer_sleep()
{
	assert (ec_tid() == EC_TID_COLLECT || ec_tid() == EC_TID_SEND);
	switch (ec_tid()) {
		case EC_TID_COLLECT:
            return &ec_states_collect.union1.timer_sleep;
		case EC_TID_SEND:
            return &ec_states_send.union1.timer_sleep;
        default:
            return 0;
	}
}
