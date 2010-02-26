#include "LogWrite.h"
#include "Queue.h"
#include "infra/debug.h"

void* logw_wire(logw_Callback* callback, const char* file)
{
	DEBUGOUT("logw_wire(%p, ...)", callback);
	return callback;	
}

typedef struct {
	void* handle;
	void* buf;
	storage_len_t len;
} AppendDoneContext;

static AppendDoneContext ctx;

static void appendDoneHandler()
{
	logw_Callback* callback = ctx.handle;
	callback->appendDone(ctx.handle, ctx.buf, ctx.len, 0, SUCCESS);	
}

error_t logw_append(void* handle, void* buf, storage_len_t len)
{
	DEBUGOUT("logw_append(%p, ...)", handle);
	ctx.handle = handle;
	ctx.buf = buf;
	ctx.len = len;
	q_push(appendDoneHandler);
    return SUCCESS;
}
