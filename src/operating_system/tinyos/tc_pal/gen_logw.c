#include "LogWrite.h"

tc_logw_wire_t tc_state_logw_wire[2];
unsigned tc_map_logw_wire(tid_t tid)
{
    return tid;
}

tc_logw_append_t tc_state_logw_append[2];
unsigned tc_map_logw_append(tid_t tid)
{
    return tid;
}
