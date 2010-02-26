#include "LogRead.h"
#include "Queue.h"

void* logr_wire(logr_Callback* callback, const char* file)
{
	return callback;	
}

typedef struct {
	void* handle;
	void* buf;
	storage_len_t len;
} ReadDoneContext;

static ReadDoneContext ctx;

static void readDoneHandler()
{
	logr_Callback* callback = ctx.handle;
	callback->readDone(ctx.handle, ctx.buf, 2 * sizeof(uint32_t), SUCCESS);	
}

error_t logr_read(void* handle, void* buf, storage_len_t len)
{
	ctx.handle = handle;
	ctx.buf = buf;
	ctx.len = len;
	q_push(readDoneHandler);
	return SUCCESS;
}

