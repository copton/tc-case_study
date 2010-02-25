#include "layout.h"
#include "infra/debug.h"
#include "threads.h"

ec_structs_collect ec_states_collect;
ec_structs_receive ec_states_receive;
ec_structs_send ec_states_send;

static inline ec_struct_log_to* ec_map_log_to()
{
	assert (ec_tid() == EC_TID_COLLECT || ec_tid() == EC_TID_RECEIVE);
    switch (ec_tid()) {
        case EC_TID_COLLECT:
            return &ec_states_collect.union1.struct1.log_to;
        case EC_TID_RECEIVE:
            return &ec_states_receive.union1.struct1.log_to;
        default:
            return 0;
    }
}

static inline ec_struct_collect_run* ec_map_collect_run()
{
	assert (ec_tid() == EC_TID_COLLECT);
	return &ec_states_collect.collect_run;
}

static inline ec_struct_aggregate_from* ec_map_aggregate_from()
{
	assert (ec_tid() == EC_TID_SEND);
    return &ec_states_send.union1.state1.aggregate_from;
}

static inline ec_struct_send_via* ec_map_send_via()
{
	assert (ec_tid() == EC_TID_SEND);
    return &ec_states_send.union1.state2.send_via;
}

static inline ec_struct_send_run* ec_map_send_run()
{
	assert (ec_tid() == EC_TID_SEND);
    return &ec_states_send.send_run;
}

static inline ec_struct_receive_run* ec_map_receive_run()
{
	assert (ec_tid() == EC_TID_RECEIVE);
	return &ec_states_receive.receive_run;
}

