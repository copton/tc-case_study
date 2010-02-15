#include "LogRead.h"

tc_logr_wire_t tc_state_logr_wire[1];
unsigned tc_map_logr_wire(tid_t tid)
{
	(void)tid;
	return 0;
}

tc_logr_read_t tc_state_logr_read[1];
unsigned tc_map_logr_read(tid_t tid)
{
	(void)tid;
	return 0;
}
