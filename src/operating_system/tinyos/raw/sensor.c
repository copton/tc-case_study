#include "infra/types.h"

typedef struct {
	bool running;
	int fd;
} Shared;

#include "component.h"
#include "sensor.h"

#include "hardware_simulation/client.h"

#include <assert.h>

void* sensor_wire(sensor_Callback* callback, const char* device)
{
	DEBUGOUT("sensor_wire\n");
	void* h = component_wire(callback);
	HANDLE;
	handle->shared.fd = hs_open(device);
	return handle;
}


static void setup(Shared* shared)
{
	shared->running = FALSE;
}

error_t sensor_read(void* h)
{
	HANDLE;
	error_t res;
	LOCK;
	if (handle->shared.running) {
		res = EBUSY;
	} else {
		handle->shared.running = TRUE;
		SIGNAL;
		res = SUCCESS;
	}
	UNLOCK;
	return res;
}

static sensor_val_t read(int fd)
{
	sensor_val_t val;
	size_t res = hs_receive(fd, (unsigned*)&val, sizeof(sensor_val_t));
	assert (res == sizeof(sensor_val_t));
	return val;
}

static void* run(void* h)
{
    HANDLE;
	int fd = handle->shared.fd;
    LOCK;
    SIGNAL;
    while(1) {
		handle->shared.running = FALSE;
		WAIT;
		UNLOCK;

		sensor_val_t val = read(fd);

		LOCK;
		cb_lock_acquire();
		((sensor_Callback*)handle->callback)->readDone(handle, SUCCESS, val);
		cb_lock_release();
	}
	UNLOCK;
}
