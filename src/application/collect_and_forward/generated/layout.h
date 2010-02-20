#ifndef PHIELAIYAICHAIYAIPEA
#define PHIELAIYAICHAIYAIPEA

#include "states.h"

typedef struct {
    ec_struct_collect_run collect_run;
    union {
        ec_struct_timer_sleep timer_sleep;
        ec_struct_sensor_read sensor_read;
        struct {
            ec_struct_log_to log_to;
            ec_struct_logw_append logw_append;
        } struct1;
    } union1;
} ec_structs_collect;
extern ec_structs_collect ec_states_collect;

typedef struct {
    ec_struct_receive_run receive_run;
    union {
        ec_struct_receive_receive receive_receive;
        struct {
            ec_struct_log_to log_to;
            ec_struct_logw_append logw_append;
        } struct1;
    } union1;
} ec_structs_receive;
extern ec_structs_receive ec_states_receive;

typedef struct {
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
} ec_structs_send;
extern ec_structs_send ec_states_send;

#endif
