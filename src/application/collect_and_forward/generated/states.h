#ifndef UOVAURAIYIPHAIKOAHEI
#define UOVAURAIYIPHAIKOAHEI

#include "LogWrite.h"
#include "Receive.h"
#include "Send.h"
#include "LogRead.h"
#include "LogWrite.h"
#include "Sensor.h"
#include "Timer.h"
#include "Receive.h"
#include "Send.h"

typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	storage_len_t len;
	//private
	storage_len_t res_len;
	bool recordsLost;
} ec_struct_log_to;

typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	unsigned dt;
	//private
	void* sensor_handle;
	void* logw_handle;
    void* timer_handle;
	uint64_t now;
	sensor_val_t val;
} ec_struct_collect_run;

typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	int32_t* min;
	int32_t* max;
	//private
	unsigned char read_buffer[250];
	storage_len_t len;
} ec_struct_aggregate_from;

typedef struct {
	ec_continuation_t ec_continuation;
	//private
	net_message_t msg;
} ec_struct_send_via;

typedef struct {
	ec_continuation_t ec_continuation;
	//signature
	unsigned dt;
	//private
	void* logr1_handle;
	void* logr2_handle;
	void* send_handle;
    void* timer_handle;
	uint64_t now;
	int32_t min;
	int32_t max;
} ec_struct_send_run;

typedef struct {
	ec_continuation_t ec_continuation;

	//private
	void* receive_handle;
	void* logw_handle;
	net_message_t* msg;
	unsigned char* payload;
	uint8_t len;
} ec_struct_receive_run;


#endif
