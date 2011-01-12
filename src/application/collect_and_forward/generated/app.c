#include <string.h>

#include "tstack.h"
#include "main.h"
#include "infra/debug.h"

#define S6 ((ec_stack_6*) cont.stack)
#define S7 ((ec_stack_7*) cont.stack)
#define S8 ((ec_stack_8*) cont.stack)
#define S9 ((ec_stack_9*) cont.stack)
#define S10 ((ec_stack_10*) cont.stack)
#define S11 ((ec_stack_11*) cont.stack)
#define S12 ((ec_stack_12*) cont.stack)
#define S13 ((ec_stack_13*) cont.stack)
#define S14 ((ec_stack_14*) cont.stack)

// from config.h
static const char* fn_receive = "/tmp/tc/receive.sock";
static const char* fn_send = "/tmp/tc/send.sock";
static const char* fn_collect ="/tmp/tc/collect.sock";
static const char* fn_flash_receive_source = "/tmp/tc/flash-receive-source.sock";
static const char* fn_flash_collect_source = "/tmp/tc/flash-collect-source.sock";
static const char* fn_flash_receive_sink = "/tmp/tc/flash-receive-sink.sock";
static const char* fn_flash_collect_sink = "/tmp/tc/flash-collect-sink.sock";
static const int dt_collect = 500;
static const int dt_send = 2000;

void ec_events(ec_continuation_t cont)
{
    union {
	    struct {
			error_t res;			
		} _6;	
		struct {
            const char* sensor;
            const char* file;
			error_t res;
		} _7;
		struct {
			const char* channel;
			const char* file;
			error_t res;
		} _9;
		struct {
			error_t res;
			void* payload;
		} _11;
		struct {
			error_t res;
			int i;
			int32_t tmp;
		} _12;
		struct {
			const char* channel;
			const char* file1;
			const char* file2;
		} _13;
    } s;

    if (cont.label != 0) goto *cont.label;

    if (ec_tid() == 1) {
		goto _14_0;
    }
    if (ec_tid() == 2) {
		goto _10_0;
    }
    if (ec_tid() == 3) {
		goto _8_0;	
    }
	assert (false);
	return;

_6_0:	S6->frames.ec_frame_0.ec_cont.label = &&_6_1;
		S6->frames.ec_frame_0.ec_cont.stack = S6;
        S6->frames.ec_frame_0.buf = S6->buf;
        S6->frames.ec_frame_0.res_len = &S6->res_len;
        S6->frames.ec_frame_0.recordsLost = &S6->recordsLost;
		ec_pal_0(&S6->frames.ec_frame_0, S6->handle, S6->len);
		return;
_6_1:	s._6.res = S6->frames.ec_frame_0.ec_result;
		assert (s._6.res == SUCCESS);
		assert (S6->res_len == S6->len);
		cont.stack = S6->ec_cont.stack;
		goto *S6->ec_cont.label;

_7_0:	S7->sensor_handle = pal_sensor_wire(S7->sensor);
		S7->logw_handle = pal_logw_wire(S7->file);
		S7->timer_handle = pal_timer_wire();
		S7->now = pal_timer_getNow(S7->timer_handle);
_7_1:	if (! true) goto _7_5;
		S7->frames.ec_frame_5.ec_cont.label = &&_7_2;
		S7->frames.ec_frame_5.ec_cont.stack = S7;
		ec_pal_5(&S7->frames.ec_frame_5, S7->timer_handle, S7->now + S7->dt);
		return;
_7_2:	S7->now += S7->dt;
		S7->frames.ec_frame_4.ec_cont.label = &&_7_3;
		S7->frames.ec_frame_4.ec_cont.stack = S7;
        S7->frames.ec_frame_4.val = &S7->val;
		ec_pal_4(&S7->frames.ec_frame_4, S7->sensor_handle);
		return;
_7_3:	s._7.res = S7->frames.ec_frame_4.ec_result;
		assert(s._7.res == SUCCESS);
		S7->frames.ec_frame_6.ec_cont.label = &&_7_4;
		S7->frames.ec_frame_6.ec_cont.stack = S7;
		S7->frames.ec_frame_6.handle = S7->logw_handle;
		S7->frames.ec_frame_6.buf = &S7->val;
		S7->frames.ec_frame_6.len = sizeof(sensor_val_t);
		cont.stack = &S7->frames.ec_frame_6;
		goto _6_0;
_7_4:	goto _7_1;
_7_5:	cont.stack = S7->ec_cont.stack;
		goto *S7->ec_cont.label;

_8_0:	(void)argc;
		(void)argv;
        s._7.sensor = fn_collect;
        s._7.file = fn_flash_collect_sink;
        S8->frames.ec_frame_7.dt = dt_collect;
        S8->frames.ec_frame_7.ec_cont.label = &&_8_1;
        S8->frames.ec_frame_7.ec_cont.stack = S8;
        cont.stack = &S8->frames.ec_frame_7;
        goto _7_0;
_8_1:	assert (false);
		return;

_9_0:	S9->receive_handle = pal_receive_wire(s._9.channel);
		S9->logw_handle = pal_logw_wire(s._9.file);
_9_1:	if (!true) goto _9_4;
		S9->frames.ec_frame_1.msg = &S9->msg;
		S9->frames.ec_frame_1.payload = &S9->payload;
		S9->frames.ec_frame_1.len = &S9->len;
		S9->frames.ec_frame_1.ec_cont.label = &&_9_2;
		S9->frames.ec_frame_1.ec_cont.stack = S9;
		ec_pal_1(&S9->frames.ec_frame_1, S9->receive_handle);
		return;
_9_2:	s._9.res = S9->frames.ec_frame_1.ec_result;
		assert (s._9.res == SUCCESS);
		S9->frames.ec_frame_6.handle = S9->logw_handle;
		S9->frames.ec_frame_6.buf = S9->payload;
		S9->frames.ec_frame_6.len = S9->len;
		S9->frames.ec_frame_6.ec_cont.label = &&_9_3;
		S9->frames.ec_frame_6.ec_cont.stack = S9;
		cont.stack = &S9->frames.ec_frame_6;	
		goto _6_0;
_9_3:	goto _9_1;
_9_4:	cont.stack = S9->ec_cont.stack;
		goto *S9->ec_cont.label;		

_10_0:	s._9.channel = fn_receive;
		s._9.file = fn_flash_receive_sink;
		S10->frames.ec_frame_9.ec_cont.label = &&_10_1;
		S10->frames.ec_frame_9.ec_cont.stack = S10;
		cont.stack = &S10->frames.ec_frame_9;
		goto _9_0;
_10_1:	assert (false);
		return;

_11_0:	s._11.payload = pal_send_getPayload(S11->handle, &S11->msg, 2 * sizeof(int32_t));
		memcpy(s._11.payload, &S11->min, sizeof(int32_t));
		memcpy(s._11.payload + sizeof(int32_t), &S11->max, sizeof(int32_t));
		S11->frames.ec_frame_2.ec_cont.label = &&_11_1;
		S11->frames.ec_frame_2.ec_cont.stack = S11;
		S11->frames.ec_frame_2.msg = &S11->msg;
		ec_pal_2(&S11->frames.ec_frame_2, S11->handle, 2*sizeof(int32_t));
		return;
_11_1:	s._11.res = S11->frames.ec_frame_2.ec_result;
		assert(s._11.res == SUCCESS);
		cont.stack = S11->ec_cont.stack;
		goto *S11->ec_cont.label;

_12_0:	S12->frames.ec_frame_3.buf = S12->read_buffer;
		S12->frames.ec_frame_3.res_len = &S12->len;
		S12->frames.ec_frame_3.ec_cont.label = &&_12_1;
		S12->frames.ec_frame_3.ec_cont.stack = S12;
		ec_pal_3(&S12->frames.ec_frame_3, S12->handle, sizeof(S12->read_buffer));
		return;
_12_1:	s._12.res = S12->frames.ec_frame_3.ec_result;
		assert(s._12.res == SUCCESS);
		assert((S12->len & sizeof(int32_t)) == 0);
		s._12.i = 0;
_12_2:	if (!(s._12.i < S12->len/sizeof(int32_t))) goto _12_3;
		memcpy(&s._12.tmp, S12->read_buffer + s._12.i * sizeof(int32_t), sizeof(int32_t));
		if (s._12.tmp < *S12->min) *S12->min=s._12.tmp;
		if (s._12.tmp > *S12->max) *S12->max=s._12.tmp;
		goto _12_2;
_12_3:  cont.stack = S12->ec_cont.stack;
		goto *S12->ec_cont.label;

_13_0:	S13->logr1_handle = pal_logr_wire(s._13.file1);
		S13->logr2_handle = pal_logr_wire(s._13.file2);
		S13->send_handle = pal_send_wire(s._13.channel);
		S13->timer_handle = pal_timer_wire();	
_13_1:	if (! true) goto _13_6;
		S13->frames.ec_frame_5.ec_cont.label = &&_13_2;
		S13->frames.ec_frame_5.ec_cont.stack = S13;
		ec_pal_5(&S13->frames.ec_frame_5, S13->timer_handle, S13->now + S13->dt);
		return;
_13_2:	S13->now += S13->dt;
		S13->min = 0x7FFFFFFF;
		S13->max = 0xFFFFFFFF; 
		S13->frames.ec_frame_12.handle = S13->logr1_handle;
		S13->frames.ec_frame_12.min = &S13->min;
		S13->frames.ec_frame_12.max = &S13->max;
		S13->frames.ec_frame_12.ec_cont.label = &&_13_3;
		S13->frames.ec_frame_12.ec_cont.stack = S13;
		goto _12_0;
_13_3:	S13->frames.ec_frame_12.handle = S13->logr2_handle;
		S13->frames.ec_frame_12.min = &S13->min;
		S13->frames.ec_frame_12.max = &S13->max;
		S13->frames.ec_frame_12.ec_cont.label = &&_13_4;
		S13->frames.ec_frame_12.ec_cont.stack = S13;
		goto _12_0;
_13_4:	S13->frames.ec_frame_11.handle = S13->send_handle;
		S13->frames.ec_frame_11.min = S13->min;
		S13->frames.ec_frame_11.max = S13->max;
		S13->frames.ec_frame_11.ec_cont.label = &&_13_5;		
		S13->frames.ec_frame_11.ec_cont.stack = S13;
		goto _11_0;
_13_5:	goto _13_1;
_13_6:	cont.stack = S13->ec_cont.stack;
		goto *S13->ec_cont.label;

_14_0:	s._13.channel = fn_send;
		s._13.file1 = fn_flash_receive_source;
		s._13.file2 = fn_flash_collect_source;
		S14->frames.ec_frame_13.dt = dt_send;
		S14->frames.ec_frame_13.ec_cont.label = &&_14_1;
		S14->frames.ec_frame_13.ec_cont.stack = S14;
		goto _13_0;
_14_1:	assert (false);
		return;
}
