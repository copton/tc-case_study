#include "LogWrite.h"
#include "Queue.h"
#include "infra/debug.h"

typedef struct {
	logw_Callback* callback;
} Handle;

static Handle handles[2];

void* logw_wire(logw_Callback* callback, const char* file)
{
	static int count = 0;
	DEBUGOUT("logw_wire(%p, ...)", callback);
	assert (count < 2);
	Handle* current = &handles[count++];
	current->callback = callback;
	return current;	
}

typedef struct {
	void* handle;
	void* buf;
	storage_len_t len;
} AppendDoneContext;

static AppendDoneContext ctx;

static void appendDoneHandler()
{
	logw_Callback* callback = ((Handle*)ctx.handle)->callback;
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
