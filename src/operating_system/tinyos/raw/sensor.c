#include "Sensor.h"
#include "infra/types.h"

typedef sensor_Callback Callback;

typedef struct {
	bool running;
	int fd;
} Shared;

#include "component.h"

#include "hardware_simulation/client.h"
#include <assert.h>
#include <arpa/inet.h>

void* sensor_wire(sensor_Callback* callback, const char* device)
{
	DEBUGOUT("sensor_wire(%p, %s)\n", callback, device);
	Handle* handle = malloc(sizeof(Handle));
	handle->callback = callback;

	handle->shared.running = FALSE;
	handle->shared.fd = hs_open(device);

	setupThread(handle);

	return handle;
}

error_t sensor_read(void* h)
{
	DEBUGOUT("sensor_read(%p)\n", h);
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
	DEBUGOUT("sensor_read(...) -> %d\n", res);
	return res;
}

static sensor_val_t read(int fd)
{
	sensor_val_t val;
	size_t res = hs_receive(fd, (unsigned*)&val, sizeof(sensor_val_t));
	assert (res == sizeof(sensor_val_t));
	return ntohl(val);
}

static void* run(void* h)
{
	DEBUGOUT("sensor::run(%p)\n", h);
    HANDLE;
    LOCK;
    SIGNAL;
	int fd = handle->shared.fd;
    while(1) {
		handle->shared.running = FALSE;
		WAIT;
		UNLOCK;

		sensor_val_t val = read(fd);

		LOCK;
		cb_lock_acquire();
		handle->callback->readDone(handle, SUCCESS, val);
		cb_lock_release();
	}
	UNLOCK;
	return NULL;
}
