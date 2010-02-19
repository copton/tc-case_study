#include "receive.h"

#include "Receive.h"
#include "LogWrite.h"
#include "infra/debug.h"
#include <stddef.h>

static void* receive_handle = NULL;
static void* logw_handle = NULL;

typedef enum {
	WAIT_RECEIVE,
	WAIT_LOG
} State;

static State state;
static net_message_t message;
static net_message_t* my_msg = &message;
static void* cur_payload;
static uint8_t cur_len;

static net_message_t* receive(void* handle, net_message_t* msg, void* payload, uint8_t len)
{
    DEBUGOUT("receive__receive(%p, %p, %p, %u)", handle, msg, payload, len);
	DEBUGOUT("receive__receive: state = %d", state);
	assert (state == WAIT_RECEIVE);
	assert (handle == receive_handle);
	assert (len == 2 * sizeof(uint32_t));

	cur_payload = payload;
	cur_len = len;

	error_t error = logw_append(logw_handle, payload, len);
	assert (error == SUCCESS);

	state = WAIT_LOG;

	net_message_t* res = my_msg;
	my_msg = msg;
    return res;
}

static void appendDone(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error)
{
    DEBUGOUT("receive__appendDone(%p, %p, %u, %d, %d)", handle, buf, len, recordsLost, error);
	assert (state == WAIT_LOG);
	assert (handle == logw_handle);
	assert (buf == cur_payload);
	assert (len == cur_len);
	(void)recordsLost;
	assert (error == SUCCESS);

	state = WAIT_RECEIVE;
}

static receive_Callback receive_callback = {&receive};
static logw_Callback logw_callback = {&appendDone, NULL};

void receive_init(const char* channel, const char* file)
{
	DEBUGOUT("receive_init(%s, %s)", channel, file);
	state = WAIT_RECEIVE;
	logw_handle = logw_wire(&logw_callback, file);
    receive_handle = receive_wire(&receive_callback, channel);
}
