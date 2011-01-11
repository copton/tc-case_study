#ifndef UOVAURAIYIPHAIKOAHEI
#define UOVAURAIYIPHAIKOAHEI

#include "LogWrite.h"
typedef ec_stack_logw_append ec_stack_0;
#define ec_pal_0(...) ec_pal_logw_append(__VA_ARGS__)

#include "Receive.h"
typedef ec_stack_receive_receive ec_stack_1;
#define ec_pal_1(...) ec_pal_receive_receive(__VA_ARGS__)

#include "Send.h"
typedef ec_stack_send_send ec_stack_2;
#define ec_pal_2(...) ec_pal_send_send(__VA_ARGS__)

#include "LogRead.h"
typedef ec_stack_logr_read ec_stack_3;
#define ec_pal_3(...) ec_pal_logr_read(__VA_ARGS__)

#include "Sensor.h"
typedef ec_stack_sensor_read ec_stack_4;
#define ec_pal_4(...) ec_pal_sensor_read(__VA_ARGS__)

#include "Timer.h"
typedef ec_stack_timer_sleep ec_stack_5;
#define ec_pal_5(...) ec_pal_timer_sleep(__VA_ARGS__)

typedef struct ec_stack_log_to {
	ec_continuation_t ec_cont;
// signature
    void* handle;
    void* buf;
	storage_len_t len;
// local
	storage_len_t res_len;
	bool recordsLost;
// next frame 
    union {
        ec_stack_0 ec_frame_0;
   } frames;
} ec_stack_6;

typedef struct ec_stack_collect_run {
    ec_continuation_t ec_cont;
// signature
    const char* sensor;
    const char* file;
    unsigned dt;
// local
    void* sensor_handle;
    void* logw_handle;
    void* timer_handle;
    uint32_t now;
    sensor_val_t val;
// next frame
    union {
        ec_stack_5 ec_frame_5;
        ec_stack_4 ec_frame_4;
        ec_stack_6 ec_frame_6;
    } frames;
} ec_stack_7;

typedef struct ec_stack_run_collect {
    union {
        ec_stack_7 ec_frame_7;
    } frames;
} ec_stack_8;

#endif
