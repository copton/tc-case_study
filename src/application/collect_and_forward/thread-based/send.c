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
