#include "Sensor.h"

typedef sensor_Callback Callback;

typedef struct {
	bool running;
	int fd;
} Shared;

#include "component.h"

#include "hardware_simulation/client.h"

void* sensor_wire(sensor_Callback* callback, const char* device)
{
	DEBUGOUT("sensor_wire(%p, %s)", callback, device);
	Handle* handle = malloc(sizeof(Handle));
	handle->callback = callback;

	handle->shared.running = false;
	handle->shared.fd = hs_open(device);

	setupThread(handle);

	return handle;
}

error_t sensor_read(void* h)
{
	DEBUGOUT("%p: sensor_read", h);
	HANDLE;
	error_t res;
	LOCK;
	if (handle->shared.running) {
		res = EBUSY;
	} else {
		handle->shared.running = true;
		SIGNAL;
		res = SUCCESS;
	}
	UNLOCK;
	DEBUGOUT("%p: sensor_read(...) -> %d", h, res);
	return res;
}

static sensor_val_t read(int fd)
{
	sensor_val_t val;
	size_t res = hs_read(fd, (unsigned char*)&val, sizeof(sensor_val_t));
	assert (res == sizeof(sensor_val_t));
	return val;
}

static void* run(void* h)
{
	DEBUGOUT("%p: sensor__run", h);
    HANDLE;
    os_sem_down();
    LOCK;
	int fd = handle->shared.fd;
    while(1) {
        if (handle->shared.running == false) {
            DEBUGOUT("%p: sensor__run: i'm waiting...", h);
            WAIT;
            DEBUGOUT("%p: sensor__run: i woke up", h);
        }
		handle->shared.running = false;
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
