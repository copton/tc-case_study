#ifndef PHIELAIYAICHAIYAIPEA
#define PHIELAIYAICHAIYAIPEA

#include "states.h"

struct {
    ec_struct_collect_run collect_run;
    union {
        ec_struct_timer_sleep timer_sleep;
        ec_struct_sensor_read sensor_read;
        struct {
            ec_struct_log_to log_to;
            ec_struct_logw_append logw_append;
        } struct1;
    } union1;
} ec_tstack_1;

struct {
    ec_struct_receive_run receive_run;
    union {
        ec_struct_receive_receive receive_receive;
        struct {
            ec_struct_log_to log_to;
            ec_struct_logw_append logw_append;
        } struct1;
    } union1;
} ec_tstack_2;

struct {
    ec_struct_send_run send_run;
    union {
        ec_struct_timer_sleep timer_sleep;
        struct {
            ec_struct_aggregate_from aggregate_from;
            ec_struct_logr_read logr_read;
        } state1;
        struct {
            ec_struct_send_via send_via;
            ec_struct_send_send send_send;
        } state2;
    } union1;
} ec_tstack_3;

#endif
