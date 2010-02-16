#include "receive.h"
#include "log.h"
#include "LogWrite.h"
#include "Receive.h"
#include <assert.h>

/*
void receive_run(const char* channel, const char* file)
{
    void* receive_handle = receive_wire(channel);
    void* logw_handle = logw_wire(file);
    while (1) {
        net_message_t msg;
        unsigned char* payload;
        uint8_t len;

		error_t res = receive_receive(receive_handle, &msg, (void**)&payload, &len);
		assert (res == SUCCESS);

		log_to(logw_handle, payload, len);
    }
}
*/

typedef struct {
	void* receive_handle;
	void* logw_handle;
	net_message_t msg;
	unsigned char* payload;
	uint8_t len;
} tc_type_receive_run;
tc_type_receive_run tc_state_receive_run;

static void tc_sub2_receive_run();
static void tc_sub3_receive_run();
static void tc_sub4_receive_run();

void receive_run(const char* channel, const char* file)
{
	tc_state_receive_run.receive_handle = pal_receive_wire(channel);
	tc_state_receive_run.logw_handle = pal_logw_wire(file);
	tc_sub2_receive_run();
}

static void tc_sub2_receive_run()
{
	tc_type_receive_receive* tc_p_receive_receive = tc_state_receive_receive + tc_map_receive_receive();

	tc_p_receive_receive->tc_continuation = tc_sub3_receive_run;
	tc_p_receive_receive->msg = &tc_state_receive_run.msg;
	tc_p_receive_receive->payload = &tc_state_receive_run.payload;
	tc_p_receive_receive->len = &tc_state_receive_run.len;
	tc_pal_receive_receive(tc_state_receive_run.receive_handle);	
}

static void tc_sub3_receive_run()
{
	tc_type_receive_receive tc_p_receive_receive = tc_state_receive_receive + tc_map_receive_receive();
	
	error_t res = tc_p_receive_receive->tc_result;
    ((res == SUCCESS) ? (void) (0) : __assert_fail ("res == SUCCESS", "_all.c", 89, __PRETTY_FUNCTION__));

	tc_type_log_to* tc_p_log_to = tc_state_log_to + tc_map_log_to();
	tc_p_log_to->tc_continuation = tc_sub4_receive_run;
	log_to(tc_state_receive_run.logw_handle, tc_state_receive_run.payload, tc_state_receive_run.len);
}

static void tc_sub4_receive_run()
{
	tc_sub2_receive_run();
}
