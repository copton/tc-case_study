#include "Sensor.h"
#include "Queue.h"

void* sensor_wire(sensor_Callback* callback, const char* device)
{
	return callback;	
}

typedef struct {
	void* handle;
} ReadDoneContext;

static ReadDoneContext ctx;

static void readDoneHandler()
{
	sensor_Callback* callback = ctx.handle;
	callback->readDone(ctx.handle, SUCCESS, 23);
}

error_t sensor_read(void* handle)
{
	ctx.handle = handle;
	q_push(readDoneHandler);
	return SUCCESS;
}

