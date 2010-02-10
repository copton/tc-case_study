#include "send.h"

#include "Timer.h"
#include "Send.h"
#include "LogRead.h"

#include "infra/debug.h"

#include <assert.h>

void* timer_handle = NULL;
void* send_handle = NULL;
void* logr_handle = NULL;

unsigned buffer[250];
net_message_t message;

typedef enum {
	WAIT_TIMER,
	WAIT_LOGR,
	WAIT_SEND
} State;

State state;

static void fired(void* handle)
{
	DEBUGOUT("send::fired(%p)\n", handle);
	assert(state == WAIT_TIMER);
    assert(handle == timer_handle);

	error_t res = logr_read(logr_handle, buffer, sizeof(buffer));
    assert (res == SUCCESS);

	state = WAIT_LOGR;
}

static void readDone(void* handle, void* buf, storage_len_t len, error_t error)
{
	DEBUGOUT("send::readDone(%p, %p, %u, %d)\n", handle, buf, len, error);
	assert(state == WAIT_LOGR);
    assert(handle == logr_handle);
	assert(buffer == buf);
	assert(len >= 0 && len <= sizeof(buffer));
	assert(error == SUCCESS);

	// XXX aggregate
	
	error_t res = send_send(send_handle, &message, 2 * sizeof(uint32_t));
	assert(res == SUCCESS);

	state = WAIT_SEND;
}

static void sendDone(void* handle, net_message_t* msg, error_t error)
{
    DEBUGOUT("send::sendDone(%p, %p, %d)\n", handle, msg, error);
	assert(state == WAIT_SEND);
	assert(handle == send_handle);
	assert(msg == &message);
	assert(error == SUCCESS);

	state = WAIT_TIMER;
}

timer_Callback timer_callback = {&fired};
logr_Callback logr_callback = {&readDone, NULL};
send_Callback send_callback = {&sendDone};

void send_init(const char* channel, const char* file, unsigned dt)
{
	DEBUGOUT("send_init(%s, %s, %u)\n", channel, file, dt);

    timer_handle = timer_wire(&timer_callback);
    send_handle = send_wire(&send_callback, channel);
	logr_handle = logr_wire(&logr_callback, file);

	state = WAIT_TIMER;
    timer_startPeriodic(timer_handle, dt);
}
