#include "tstack.h"
#include "main.h"
#include "infra/debug.h"

#define S6 ((ec_stack_6*) cont.stack)
#define S7 ((ec_stack_7*) cont.stack)
#define S8 ((ec_stack_8*) cont.stack)


// from config.h
/* static const char* fn_receive = "/tmp/tc/receive.sock"; */
/* static const char* fn_send = "/tmp/tc/send.sock"; */
static const char* fn_collect ="/tmp/tc/collect.sock";
/* static const char* fn_flash_receive_source = "/tmp/tc/flash-receive-source.sock"; */
/* static const char* fn_flash_collect_source = "/tmp/tc/flash-collect-source.sock"; */
/* static const char* fn_flash_receive_sink = "/tmp/tc/flash-receive-sink.sock"; */
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
			error_t res;
            const char* sensor;
            const char* file;
		} _7;

    } s;

    if (cont.label != 0) goto *cont.label;

    if (ec_tid() == 1) {
    }
    if (ec_tid() == 2) {
    }
    if (ec_tid() == 3) {
        s._7.sensor = fn_collect;
        s._7.file = fn_flash_collect_sink;
        S8->frames.ec_frame_7.dt = dt_collect;
        cont.stack = &S8->frames.ec_frame_7;
        goto _7_0;
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
}
