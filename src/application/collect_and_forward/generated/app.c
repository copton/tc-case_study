#include "layout.h"
#include "main.h"

#define S1 ((ec_struct_log_to*) continuation.stack)
#define S2 ((ec_struct_collect_run*) continuation.stack)
#define S3 ((ec_struct_aggregate_from*) continuation.stack)
#define S4 ((ec_struct_send_via*) continuation.stack)
#define S5 ((ec_struct_send_run*) continuation.stack)
#define S6 ((ec_struct_receive_run*) continuation.stack)


void ec_events(ec_continuation_t continuation)
{
    union {
        struct {
            const char* sensor;
            const char* file;
            unsigned dt;
        } _2;

        struct {
            const char* channel;
            const char* file1;
            const char* file2;
            unsigned dt;
        } _5;

        struct {
            const char* channel;
            const char* file;
        } _6;
    } s;

    if (continuation.label != 0) goto *continuation.label;

    if (tid == 0) {
        s._5.channel = fn_flash_send;
        s._5.file1 = fn_flash_receive_source;
        s._5.file2 = fn_flash_collect_source;
        s._5.dt = dt_send;
        continuation.stack = 
        goto _5_1;
    }
    if (tid == 1) {
        s._6.channel = fn_receive;
        s._6.file = fn_flash_receive_sink;
        goto _6_1;
    }
    if (tid == 2) {
        s._2.sensor = fn_collect;
        s._2.file = fn_flash_collect_sink;
        s._2.dt = dt_collect;
        goto _2_1;
    }

	{
_2_1: 
        S2->sensor_handle = sensor_wire(s._2.sensor);
        S2->logw_handle = logw_wire(s._2.file);
        S2->timer_handle = timer_wire();
        S2->now = timer_getNow(S2->timer_handle);
_2_2:
        if (! true) goto XXX;
        
        
collection_run_3: ;
	}
}
