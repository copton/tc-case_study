#include "collect.h"
#include "log.h"
#include "Sensor.h"
#include "LogWrite.h"
#include "Timer.h"
#include "infra/debug.h"

void collect_run(const char* sensor, const char* file, unsigned dt)
{
    void* sensor_handle = sensor_wire(sensor);
    void* logw_handle = logw_wire(file);
	void* timer_handle = timer_wire();

    uint32_t now = timer_getNow(timer_handle);
    while (true) {
        timer_sleep(timer_handle, now + dt);
        now += dt;

        sensor_val_t val;
		error_t res = sensor_read(sensor_handle, &val);
		assert (res == SUCCESS);

        log_to(logw_handle, &val, sizeof(sensor_val_t));
    }
}
#include "infra/types.h"
#include "LogWrite.h"
#include "infra/debug.h"

void log_to(void* handle, void* buf, storage_len_t len)
{
    storage_len_t res_len;
    bool recordsLost;
    error_t res = logw_append(handle, buf, len, &res_len, &recordsLost);
    assert (res == SUCCESS);
    assert (res_len == len);
}
#include <pthread.h>
#include "send.h"
#include "receive.h"
#include "collect.h"
#include "infra/types.h"
#include "infra/debug.h"
#include "config.h"

static void* run_send(void* args)
{
	(void)args;
	send_run(fn_send, fn_flash_receive_source, fn_flash_collect_source, dt_send);
	assert (false);
	return NULL;
}

static void* run_receive(void* args)
{
	(void)args;
	receive_run(fn_receive, fn_flash_receive_sink);
	assert (false);
	return NULL;
}

static void* run_collect(void* args)
{
	(void)args;
	collect_run(fn_collect, fn_flash_collect_sink, dt_collect);
	assert (false);
	return NULL;
}

int main()
{
	pthread_t send_thread;
	pthread_t receive_thread;
	pthread_t collect_thread;
	
	pthread_create(&send_thread, NULL, run_send, NULL);
	pthread_create(&receive_thread, NULL, run_receive, NULL);
	pthread_create(&collect_thread, NULL, run_collect, NULL);

	pthread_cond_t cond;
	pthread_mutex_t mutex;
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	while(1) {
		pthread_cond_wait(&cond, &mutex);
	}

	return 0;
}
#include "receive.h"
#include "log.h"
#include "LogWrite.h"
#include "Receive.h"
#include "infra/debug.h"

void receive_run(const char* channel, const char* file)
{
    void* receive_handle = receive_wire(channel);
    void* logw_handle = logw_wire(file);
    while (true) {
        net_message_t msg;
        void* payload;
        uint8_t len;

		error_t res = receive_receive(receive_handle, &msg, &payload, &len);
		assert (res == SUCCESS);

		log_to(logw_handle, payload, len);
    }
}
#include "send.h"
#include "Timer.h"
#include "LogRead.h"
#include "Send.h"
#include <string.h>
#include "infra/debug.h"

static void aggregate_from(void* handle, int32_t* min, int32_t* max)
{
    unsigned char read_buffer[log_buffer_size];
    storage_len_t len;

    error_t res = logr_read(handle, read_buffer, sizeof(read_buffer), &len);
    assert (res == SUCCESS);
    assert((len % sizeof(int32_t)) == 0);

    { int i;
        for (i=0; i< len / sizeof(int32_t); i++) {
            int32_t tmp;
            memcpy(&tmp, read_buffer + i * sizeof(int32_t), sizeof(int32_t));
            if (tmp < *min) *min = tmp;
            if (tmp > *max) *max = tmp;
        }
    }
}

static void send_via(void* handle, int32_t min, int32_t max)
{
    net_message_t msg;
    void* payload = send_getPayload(handle, &msg, 2 * sizeof(int32_t));
    memcpy(payload, &min, sizeof(int32_t));
    memcpy(payload + sizeof(int32_t), &max, sizeof(int32_t));

    error_t res = send_send(handle, &msg, 2 * sizeof(int32_t));
    assert(res == SUCCESS);
}

void send_run(const char* channel, const char* file1, const char* file2, unsigned dt)
{
    void* logr1_handle = logr_wire(file1);
    void* logr2_handle = logr_wire(file2);
    void* send_handle = send_wire(channel);
	void* timer_handle = timer_wire();
    uint32_t now = timer_getNow(timer_handle);

    while (true) {
        timer_sleep(timer_handle, now + dt);
        now += dt;

        int32_t min = 0x7FFFFFFF;
        int32_t max = 0xFFFFFFFF;

        aggregate_from(logr1_handle, &min, &max);
        aggregate_from(logr2_handle, &min, &max);

        send_via(send_handle, min, max); 
    } 
}
