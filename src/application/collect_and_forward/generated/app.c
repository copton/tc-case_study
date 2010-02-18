#include "compiler/ec.h"

#include "threads.h"

#include "infra/types.h"
#include "LogWrite.h"
#include "Receive.h"
#include "Send.h"
#include "LogRead.h"
#include "LogWrite.h"
#include "Sensor.h"
#include "Timer.h"
#include "Receive.h"
#include "Send.h"
#include <assert.h>
#include <string.h>

/*** log_to ***/

typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	storage_len_t len;
	//private
	storage_len_t res_len;
	bool recordsLost;
} ec_struct_log_to;

ec_struct_log_to ec_state_log_to[2];

inline unsigned ec_map_log_to()
{
	assert (ec_tid == EC_TID_COLLECT || ec_tid == EC_TID_RECEIVE);
	return ec_tid;	
}

void ec_sub2_log_to();

void log_to(void* handle, void* buf)
{
	ec_struct_logw_append* ec_p_logw_append = ec_state_logw_append + ec_map_logw_append();
	ec_struct_log_to* ec_p_log_to = ec_state_log_to + ec_map_log_to();
	
	ec_p_logw_append->buf = buf;
	ec_p_logw_append->res_len = &ec_p_log_to->res_len;
	ec_p_logw_append->recordsLost = &ec_p_log_to->recordsLost;
	ec_p_logw_append->ec_continuation = ec_sub2_log_to;
	ec_pal_logw_append(handle, ec_p_log_to->len);
}

void ec_sub2_log_to()
{
	ec_struct_logw_append* ec_p_logw_append = ec_state_logw_append + ec_map_logw_append();
	ec_struct_log_to* ec_p_log_to = ec_state_log_to + ec_map_log_to();

	error_t res = ec_p_logw_append->ec_result;
	assert (res == SUCCESS);
	assert (ec_p_log_to->res_len == ec_p_log_to->len);

	ec_p_log_to->ec_continuation();	
}


/*** collect_run ***/

typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	unsigned dt;
	//private
	void* sensor_handle;
	void* logw_handle;
	uint64_t now;
	sensor_val_t val;
} ec_struct_collect_run;

ec_struct_collect_run ec_state_collect_run[1];

inline unsigned ec_map_collect_run()
{
	assert (ec_tid == EC_TID_COLLECT);
	return 0;
}

void ec_sub2_collect_run();
void ec_sub3_collect_run();
void ec_sub4_collect_run();
void ec_sub5_collect_run();
void ec_sub6_collect_run();

void collect_run(const char* sensor, const char* file)
{
	ec_struct_collect_run* ec_p_collect_run = ec_state_collect_run + ec_map_collect_run();	

	ec_p_collect_run->sensor_handle = pal_sensor_wire(sensor);

	ec_p_collect_run->logw_handle = pal_logw_wire(file);
	ec_p_collect_run->now = pal_timer_getNow();
	ec_sub2_collect_run();	
}

void ec_sub2_collect_run()
{
	ec_struct_timer_sleep* ec_p_timer_sleep = ec_state_timer_sleep + ec_map_timer_sleep();
	ec_struct_collect_run* ec_p_collect_run = ec_state_collect_run + ec_map_collect_run();

	if (! TRUE) {
		ec_sub6_collect_run();
	} else {
		ec_p_timer_sleep->ec_continuation = ec_sub3_collect_run;
		ec_pal_timer_sleep(ec_p_collect_run->now + ec_p_collect_run->dt);
	}
}

void ec_sub3_collect_run()
{
	ec_struct_collect_run* ec_p_collect_run = ec_state_collect_run + ec_map_collect_run();
	ec_struct_sensor_read* ec_p_sensor_read = ec_state_sensor_read + ec_map_sensor_read();

	ec_p_collect_run->now += ec_p_collect_run->dt;
	
	ec_p_sensor_read->val = &ec_p_collect_run->val;
	ec_p_sensor_read->ec_continuation = ec_sub4_collect_run;
	ec_pal_sensor_read(ec_p_collect_run->sensor_handle);
}

void ec_sub4_collect_run()
{
	ec_struct_collect_run* ec_p_collect_run = ec_state_collect_run + ec_map_collect_run();
	ec_struct_sensor_read* ec_p_sensor_read = ec_state_sensor_read + ec_map_sensor_read();
	ec_struct_log_to* ec_p_log_to = ec_state_log_to + ec_map_log_to();

	error_t res = ec_p_sensor_read->ec_result;
	assert (res == SUCCESS);

	ec_p_log_to->len = sizeof(sensor_val_t);
	ec_p_log_to->ec_continuation = ec_sub5_collect_run;
	log_to(ec_p_collect_run->logw_handle, &ec_p_collect_run->val);		
}

void ec_sub5_collect_run()
{
	ec_sub2_collect_run();
}

void ec_sub6_collect_run()
{
	ec_struct_collect_run* ec_p_collect_run = ec_state_collect_run + ec_map_collect_run();
	ec_p_collect_run->ec_continuation();
}

/*** aggregate_from ***/
typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	int32_t* min;
	int32_t* max;
	//private
	unsigned char read_buffer[250];
	storage_len_t len;
} ec_struct_aggregate_from;
ec_struct_aggregate_from ec_state_aggregate_from[1];

inline unsigned ec_map_aggregate_from()
{
	assert (ec_tid == EC_TID_SEND);
	return 0;
}

void ec_sub2_aggregate_from();

void aggregate_from(void* handle)
{
	ec_struct_logr_read* ec_p_logr_read = ec_state_logr_read + ec_map_logr_read();
	ec_struct_aggregate_from* ec_p_aggregate_from = ec_state_aggregate_from + ec_map_aggregate_from();

	ec_p_logr_read->buf = ec_p_aggregate_from->read_buffer;
	ec_p_logr_read->res_len = &ec_p_aggregate_from->len;
	ec_p_logr_read->ec_continuation = ec_sub2_aggregate_from;
	ec_pal_logr_read(handle, sizeof(ec_p_aggregate_from->read_buffer));
}

void ec_sub2_aggregate_from()
{
	ec_struct_logr_read* ec_p_logr_read = ec_state_logr_read + ec_map_logr_read();
	ec_struct_aggregate_from* ec_p_aggregate_from = ec_state_aggregate_from + ec_map_aggregate_from();

	error_t res = ec_p_logr_read->ec_result;
	assert (res == SUCCESS);
	assert ((ec_p_aggregate_from->len % sizeof(int32_t)) == 0);

    { int i;
        for (i=0; i< ec_p_aggregate_from->len / sizeof(int32_t); i++) {
            int32_t tmp;
            memcpy(&tmp, ec_p_aggregate_from->read_buffer + i * sizeof(int32_t), sizeof(int32_t));
            if (tmp < *ec_p_aggregate_from->min) *ec_p_aggregate_from->min = tmp;
            if (tmp > *ec_p_aggregate_from->max) *ec_p_aggregate_from->max = tmp;
        }
    }
}

/*** send_via ***/
typedef struct {
	ec_continuation_t ec_continuation;
	//private
	net_message_t msg;
} ec_struct_send_via;
ec_struct_send_via ec_state_send_via[1];

inline unsigned ec_map_send_via()
{
	assert (ec_tid == EC_TID_SEND);
	return 0;
}

void ec_sub2_send_via();

void send_via(void* handle, int32_t min, int32_t max)
{
	ec_struct_send_via* ec_p_send_via = ec_state_send_via + ec_map_send_via();
	ec_struct_send_send* ec_p_send_send = ec_state_send_send + ec_map_send_send();

	unsigned char* payload = pal_send_getPayload(handle, &ec_p_send_via->msg, 2*sizeof(int32_t));
	memcpy(payload, &min, sizeof(int32_t));
	memcpy(payload + sizeof(int32_t), &max, sizeof(int32_t));

	ec_p_send_send->msg = &ec_p_send_via->msg;
	ec_p_send_send->ec_continuation = ec_sub2_send_via;
	ec_pal_send_send(handle, 2*sizeof(int32_t));
}

void ec_sub2_send_via()
{
	ec_struct_send_via* ec_p_send_via = ec_state_send_via + ec_map_send_via();
	ec_struct_send_send* ec_p_send_send = ec_state_send_send + ec_map_send_send();

	error_t res = ec_p_send_send->ec_result;
	assert (res == SUCCESS);

	ec_p_send_via->ec_continuation();
}

/*** send_run ***/

typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	unsigned dt;
	//private
	void* logr1_handle;
	void* logr2_handle;
	void* send_handle;
	uint64_t now;
	int32_t min;
	int32_t max;
} ec_struct_send_run;
ec_struct_send_run ec_state_send_run[1];
inline unsigned ec_map_send_run()
{
	assert (ec_tid == EC_TID_SEND);
	return 0;
}

void ec_sub2_send_run();
void ec_sub3_send_run();
void ec_sub4_send_run();
void ec_sub5_send_run();
void ec_sub6_send_run();
void ec_sub7_send_run();

void send_run(const char* channel, const char* file1, const char* file2)
{
	ec_struct_send_run* ec_p_send_run = ec_state_send_run + ec_map_send_run();

	ec_p_send_run->logr1_handle = pal_logr_wire(file1);	
	ec_p_send_run->logr2_handle = pal_logr_wire(file2);	

	ec_p_send_run->now = pal_timer_getNow();
	ec_sub2_send_run();
}

void ec_sub2_send_run()
{
	ec_struct_timer_sleep* ec_p_timer_sleep = ec_state_timer_sleep + ec_map_timer_sleep();
	ec_struct_send_run* ec_p_send_run = ec_state_send_run + ec_map_send_run();

	if (! TRUE) {
		ec_sub7_send_run();
	} else {
		ec_p_timer_sleep->ec_continuation = ec_sub3_send_run;
		ec_pal_timer_sleep(ec_p_send_run->dt);		
	}
}

void ec_sub3_send_run()
{
	ec_struct_send_run* ec_p_send_run = ec_state_send_run + ec_map_send_run();
	ec_struct_aggregate_from* ec_p_aggregate_from = ec_state_aggregate_from + ec_map_aggregate_from();
		
	ec_p_send_run->now += ec_p_send_run->dt;
	ec_p_send_run->min = 0x7FFFFFFF;
	ec_p_send_run->max = 0xFFFFFFFF;

	ec_p_aggregate_from->min = &ec_p_send_run->min;
	ec_p_aggregate_from->max = &ec_p_send_run->max;
	ec_p_aggregate_from->ec_continuation = ec_sub4_send_run;
	aggregate_from(ec_p_send_run->logr1_handle);
}

void ec_sub4_send_run()
{
	ec_struct_send_run* ec_p_send_run = ec_state_send_run + ec_map_send_run();
	ec_struct_aggregate_from* ec_p_aggregate_from = ec_state_aggregate_from + ec_map_aggregate_from();
	
	ec_p_aggregate_from->min = &ec_p_send_run->min;
	ec_p_aggregate_from->max = &ec_p_send_run->max;
	ec_p_aggregate_from->ec_continuation = ec_sub5_send_run;
	aggregate_from(ec_p_send_run->logr2_handle);
}

void ec_sub5_send_run()
{
	ec_struct_send_run* ec_p_send_run = ec_state_send_run + ec_map_send_run();
	ec_struct_send_via* ec_p_send_via = ec_state_send_via + ec_map_send_via();

	ec_p_send_via->ec_continuation = ec_sub6_send_run;
	send_via(ec_p_send_run->send_handle, ec_p_send_run->min, ec_p_send_run->max);	
}

void ec_sub6_send_run()
{
	ec_sub2_send_run();
}

void ec_sub7_send_run()
{
	ec_struct_send_run* ec_p_send_run = ec_state_send_run + ec_map_send_run();

	ec_p_send_run->ec_continuation();
}

/*** receive_run ***/

typedef struct {
	ec_continuation_t ec_continuation;

	//private
	void* receive_handle;
	void* logw_handle;
	net_message_t* msg;
	unsigned char* payload;
	uint8_t len;
} ec_struct_receive_run;
ec_struct_receive_run ec_state_receive_run[1];

inline unsigned ec_map_receive_run()
{
	assert (ec_tid == EC_TID_RECEIVE);
	return 0;
}

static void ec_sub2_receive_run();
static void ec_sub3_receive_run();
static void ec_sub4_receive_run();
static void ec_sub5_receive_run();

void receive_run(const char* channel, const char* file)
{
    ec_struct_receive_run* ec_p_receive_run = ec_state_receive_run + ec_map_receive_run();

	ec_p_receive_run->receive_handle = pal_receive_wire(channel);
    ec_state_receive_run->logw_handle = pal_logw_wire(file);

	ec_sub2_receive_run();
}

static void ec_sub2_receive_run()
{
    ec_struct_receive_receive* ec_p_receive_receive = ec_state_receive_receive + ec_map_receive_receive();
	ec_struct_receive_run* ec_p_receive_run = ec_state_receive_run + ec_map_receive_run();

    if (! TRUE) {
        ec_sub4_receive_run();
    } else {
        ec_p_receive_receive->msg = &ec_p_receive_run->msg;
        ec_p_receive_receive->payload = (void**)&ec_p_receive_run->payload;
        ec_p_receive_receive->len = &ec_p_receive_run->len;
        ec_p_receive_receive->ec_continuation = ec_sub3_receive_run;
        ec_pal_receive_receive(ec_p_receive_run->receive_handle);	
    }
}

static void ec_sub3_receive_run()
{
	ec_struct_receive_run* ec_p_receive_run = ec_state_receive_run + ec_map_receive_run();
	ec_struct_receive_receive* ec_p_receive_receive = ec_state_receive_receive + ec_map_receive_receive();
	ec_struct_log_to* ec_p_log_to = ec_state_log_to + ec_map_log_to();
	
	error_t res = ec_p_receive_receive->ec_result;
    assert (res==SUCCESS);

	ec_p_log_to->len = ec_p_receive_run->len;
	ec_p_log_to->ec_continuation = ec_sub4_receive_run;
	log_to(ec_p_receive_run->logw_handle, ec_p_receive_run->payload);
}

static void ec_sub4_receive_run()
{
	ec_sub2_receive_run();
}

static void ec_sub5_receive_run()
{
    ec_struct_receive_run* ec_p_receive_run = ec_state_receive_run + ec_map_receive_run();
    ec_p_receive_run->ec_continuation();
}

/*** main ***/

const char* fn_receive = "/tmp/tc/receive.sock";
const char* fn_send = "/tmp/tc/send.sock";
const char* fn_collect ="/tmp/tc/collect.sock";
const char* fn_flash_receive_source = "/tmp/tc/flash-receive-source.sock";
const char* fn_flash_collect_source = "/tmp/tc/flash-collect-source.sock";
const char* fn_flash_receive_sink = "/tmp/tc/flash-receive-sink.sock";
const char* fn_flash_collect_sink = "/tmp/tc/flash-collect-sink.sock";

const int dt_collect = 500;
const int dt_send = 2000;


void ec_sub2_run_send();

static void run_send()
{
	ec_struct_send_run* ec_p_send_run = ec_state_send_run + ec_map_send_run();

	ec_p_send_run->dt = dt_send;
	ec_p_send_run->ec_continuation = ec_sub2_run_send;
    send_run(fn_send, fn_flash_receive_source, fn_flash_collect_source);
}

void ec_sub2_run_send()
{
    assert (FALSE);
}

void ec_sub2_run_receive();

static void run_receive()
{
	ec_struct_receive_run* ec_p_receive_run = ec_state_receive_run + ec_map_receive_run();
	
	ec_p_receive_run->ec_continuation = ec_sub2_run_receive;
    receive_run(fn_receive, fn_flash_receive_sink);
}

void ec_sub2_run_receive() {
    assert (FALSE);
}

void ec_sub2_run_collect();

static void run_collect()
{
	ec_struct_collect_run* ec_p_collect_run = ec_state_collect_run + ec_map_collect_run();

	ec_p_collect_run->dt = dt_collect;
	ec_p_collect_run->ec_continuation = ec_sub2_run_collect;
    collect_run(fn_collect, fn_flash_collect_sink);
}

void ec_sub2_run_collect()
{
    assert (FALSE);
}

int main()
{
    RUN_THREADS(run_send, run_receive, run_collect);
    assert (FALSE);

    return 0;
}

