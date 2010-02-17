/*
#include "receive.h"
#include "log.h"
#include "LogWrite.h"
#include "Receive.h"
#include <assert.h>

void receive_run(const char* channel, const char* file)
{
    void* receive_handle = receive_wire(channel);
    void* logw_handle = logw_wire(file);
    while (TRUE) {
        net_message_t* msg;
        unsigned char* payload;
        uint8_t len;

		error_t res = receive_receive(receive_handle, &msg, (void**)&payload, &len);
		assert (res == SUCCESS);

		log_to(logw_handle, payload, len);
    }
}
*/

#include "compiler/ec.h"
#include "receive.h"
#include "log.h"
#include "LogWrite.h"
#include "Receive.h"
#include <assert.h>

typedef struct {
	void* receive_handle;
	void* logw_handle;
	net_message_t* msg;
	unsigned char* payload;
	uint8_t len;
} ec_struct_receive_run;
ec_struct_receive_run ec_state_receive_run;

static void ec_sub2_receive_run();
static void ec_sub3_receive_run();
static void ec_sub4_receive_run();

void receive_run(const char* channel, const char* file)
{
	ec_state_receive_run.receive_handle = pal_receive_wire(channel);
	ec_state_receive_run.logw_handle = pal_logw_wire(file);
	ec_sub2_receive_run();
}

static void ec_sub2_receive_run()
{
	ec_struct_receive_receive* ec_p_receive_receive = ec_state_receive_receive + ec_map_receive_receive();

	ec_p_receive_receive->ec_continuation = ec_sub3_receive_run;
	ec_p_receive_receive->msg = &ec_state_receive_run.msg;
	ec_p_receive_receive->payload = (void**)&ec_state_receive_run.payload;
	ec_p_receive_receive->len = &ec_state_receive_run.len;
	ec_pal_receive_receive(ec_state_receive_run.receive_handle);	
}

static void ec_sub3_receive_run()
{
	ec_struct_receive_receive* ec_p_receive_receive = ec_state_receive_receive + ec_map_receive_receive();
	
	error_t res = ec_p_receive_receive->ec_result;
    ((res == SUCCESS) ? (void) (0) : __assert_fail ("res == SUCCESS", "_all.c", 89, __PRETTY_FUNCTION__));

	ec_struct_log_to* ec_p_log_to = ec_state_log_to + ec_map_log_to();
	ec_p_log_to->ec_continuation = ec_sub4_receive_run;
	log_to(ec_state_receive_run.logw_handle, ec_state_receive_run.payload, ec_state_receive_run.len);
}

static void ec_sub4_receive_run()
{
	ec_sub2_receive_run();
}
