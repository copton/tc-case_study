#include "send.h"

#include "Timer.h"
#include "Send.h"
#include "LogRead.h"

#include "infra/debug.h"

#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

static void* timer_handle = NULL;
static void* send_handle = NULL;
static void* logr_handle = NULL;

static unsigned buffer[250];
static net_message_t message;

typedef enum {
	WAIT_TIMER,
	WAIT_LOGR,
	WAIT_SEND
} State;

static State state;

static void fired(void* handle)
{
	DEBUGOUT("send::fired(%p)", handle);
	assert(state == WAIT_TIMER);
    assert(handle == timer_handle);

	error_t res = logr_read(logr_handle, buffer, sizeof(buffer));
    assert (res == SUCCESS);

	state = WAIT_LOGR;
}

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
	DEBUGOUT("send::readDone(%p, %p, %u, %d)", handle, buf, len, error);
	assert(state == WAIT_LOGR);
    assert(handle == logr_handle);
	assert(buffer == buf);
	assert(len >= 0 && len <= sizeof(buffer));
	assert(error == SUCCESS);

	assert((len % sizeof(int32_t)) == 0);
	int32_t min = 0x7FFFFFFF;
	int32_t max = 0xFFFFFFFF;
	{ int i;
		for (i=0; i< len / sizeof(int32_t); i++) {
			int32_t tmp;
			memcpy(&tmp, (unsigned*)buf + i * 4, sizeof(int32_t));
			tmp = ntohl(tmp);
			if (tmp < min) min = tmp;
			if (tmp > max) max = tmp;	
		}
	}
	
	min = htonl(min);
	max = htonl(max);
	memcpy(message.buffer, &min, sizeof(int32_t));
	memcpy(message.buffer + sizeof(int32_t), &max, sizeof(int32_t));
	
	error_t res = send_send(send_handle, &message, 2 * sizeof(uint32_t));
	assert(res == SUCCESS);

	state = WAIT_SEND;
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
static logr_Callback logr_callback = {&readDone, NULL};
static send_Callback send_callback = {&sendDone};

void send_init(const char* channel, const char* file, unsigned dt)
{
	DEBUGOUT("send_init(%s, %s, %u)", channel, file, dt);

    timer_handle = timer_wire(&timer_callback);
    send_handle = send_wire(&send_callback, channel);
	logr_handle = logr_wire(&logr_callback, file);

	state = WAIT_TIMER;
    timer_startPeriodic(timer_handle, dt);
}
