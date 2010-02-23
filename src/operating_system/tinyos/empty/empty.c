#include "LogRead.h"
#include "LogTypes.h"
#include "LogWrite.h"
#include "NetTypes.h"
#include "Receive.h"
#include "Send.h"
#include "Sensor.h"
#include "SensorTypes.h"
#include "Timer.h"
#include "Types.h"
#include "Os.h"

void* logr_wire(logr_Callback* callback, const char* file) { return 0; }
error_t logr_read(void* handle, void* buf, storage_len_t len) { return 0; }
storage_cookie_t logr_currentOffset(void* handle) { return 0; }
error_t logr_seek(void* handle, storage_cookie_t offset) { return 0; }
storage_len_t logr_getSize(void* handle) { return 0; }

void* logw_wire(logw_Callback* callback, const char* file) { return 0; }
error_t logw_append(void* handle, void* buf, storage_len_t len) { return 0; }
storage_cookie_t logw_currentOffset(void* handle) { return 0; }
error_t logw_erase(void* handle) { return 0; }
error_t logw_sync(void* handle) { return 0; }

void* receive_wire(receive_Callback* callback, const char* channel) { return 0; }
void* send_wire(send_Callback* callback, const char* channel) { return 0; }
error_t send_send(void* handle, net_message_t* msg, uint8_t len) { return 0; }
error_t send_cancel(void* handle, net_message_t* msg) { return 0; }
uint8_t send_maxPayloadLength(void* handle) { return 0; }
void* send_getPayload(void* handle, net_message_t* msg, uint8_t len) { return 0; }
void* sensor_wire(sensor_Callback* callback, const char* device) { return 0; }
error_t sensor_read(void* handle) { return 0; }
void* timer_wire(timer_Callback* callback) { return 0; }
void timer_startPeriodic(void* handle, uint32_t dt) { }
void timer_startOneShot(void* handle, uint32_t dt) { }
void timer_stop(void* handle) { }
bool timer_isRunning(void* handle) { return 0; }
bool timer_isOneShot(void* handle) { return 0; }
void timer_startPeriodicAt(void* handle, uint32_t t0, uint32_t dt) { }
void timer_startOneShotAt(void* handle, uint32_t t0, uint32_t dt) { }
uint32_t timer_getNow(void* handle) { return 0; }
uint32_t timer_gett0(void* handle) { return 0; }
uint32_t timer_getdt(void* handle) { return 0; }

void os_init() { }
void os_run() { }
