#include "send.h"

#include "Timer.h"
#include "Send.h"
#include "LogRead.h"

#include "infra/debug.h"
#include "infra/types.h"

#include <assert.h>
#include <string.h>

static void* timer_handle = NULL;
static void* send_handle = NULL;
static void* logr_handle_1 = NULL;
static void* logr_handle_2 = NULL;
static int32_t min;
static int32_t max;

static unsigned char read_buffer[250];
static net_message_t message;

typedef enum {
	WAIT_TIMER,
	WAIT_LOGR_1,
	WAIT_LOGR_2,
	WAIT_SEND
} State;

static State state;

static void fired(void* handle)
{
	DEBUGOUT("send::fired(%p)", handle);
	assert(state == WAIT_TIMER);
    assert(handle == timer_handle);

	error_t res = logr_read(logr_handle_1, read_buffer, sizeof(read_buffer));
    assert (res == SUCCESS);

	state = WAIT_LOGR_1;
}

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
	DEBUGOUT("send::readDone(%p, %p, %u, %d)", handle, buf, len, error);
    if (state == WAIT_LOGR_1) {
        assert (handle == logr_handle_1);
        min = 0x7FFFFFFF;
        max = 0xFFFFFFFF;
    } else if (state == WAIT_LOGR_2) {
        assert (handle == logr_handle_2);
    } else {
        assert (FALSE);
    }
	assert(read_buffer == buf);
	assert(len >= 0 && len <= sizeof(read_buffer));
	assert(error == SUCCESS);

	assert((len % sizeof(int32_t)) == 0);

	{ int i;
		for (i=0; i< len / sizeof(int32_t); i++) {
			int32_t tmp;
			memcpy(&tmp, read_buffer + i * sizeof(int32_t), sizeof(int32_t));
			if (tmp < min) min = tmp;
			if (tmp > max) max = tmp;	
		}
	}
	
    if (state == WAIT_LOGR_1) {
        error_t res = logr_read(logr_handle_2, read_buffer, sizeof(read_buffer));
        assert (res == SUCCESS);
        state = WAIT_LOGR_2;
    } else {
        memcpy(message.buffer, &min, sizeof(int32_t));
        memcpy(message.buffer + sizeof(int32_t), &max, sizeof(int32_t));
        
        error_t res = send_send(send_handle, &message, 2 * sizeof(uint32_t));
        assert(res == SUCCESS);

        state = WAIT_SEND;
    }
}

static void sendDone(void* handle, net_message_t* msg, error_t error)
{
    DEBUGOUT("send::sendDone(%p, %p, %d)", handle, msg, error);
	assert(state == WAIT_SEND);
	assert(handle == send_handle);
	assert(msg == &message);
	assert(error == SUCCESS);

	state = WAIT_TIMER;
}

static timer_Callback timer_callback = {&fired};
static send_Callback send_callback = {&sendDone};
static logr_Callback logr_callback = {&readDone, NULL};

void send_init(const char* channel, const char* file1, const char* file2, unsigned dt)
{
	DEBUGOUT("send_init(%s, %s, %s, %u)", channel, file1, file2, dt);

    timer_handle = timer_wire(&timer_callback);
    send_handle = send_wire(&send_callback, channel);
	logr_handle_1 = logr_wire(&logr_callback, file1);
	logr_handle_2 = logr_wire(&logr_callback, file2);

	state = WAIT_TIMER;
    timer_startPeriodic(timer_handle, dt);
}
