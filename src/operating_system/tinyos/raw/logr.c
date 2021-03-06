#include "LogRead.h"

typedef logr_Callback Callback;

typedef struct {
    int fd;
    void* buf;
    storage_len_t len;
} Shared;

#include "component.h"

#include "hardware_simulation/client.h"

void* logr_wire(logr_Callback* callback, const char* file)
{
	DEBUGOUT("logr_wire(%p, %s)", callback, file);
	Handle* handle = malloc(sizeof(Handle));
	handle->callback = callback;

	handle->shared.fd = hs_open(file);
	handle->shared.buf = NULL;
	handle->shared.len = 0;

	setupThread(handle);

	DEBUGOUT("logr_wire(...) -> %p", handle);
	return handle;
}

error_t logr_read(void* h, void* buf, storage_len_t len)
{
	DEBUGOUT("%p: logr_read(%p, %p, %u)", h, h, buf, len);
	HANDLE;
	error_t res;
	LOCK;
	if (handle->shared.buf) {
		res = EBUSY;
	} else {
		handle->shared.buf = buf;
        handle->shared.len = len;
		SIGNAL;
		res = SUCCESS;
	}
	UNLOCK;
	DEBUGOUT("%p: logr_read(...) -> %d", h, res);
	return res;
}

storage_cookie_t logr_currentOffset(void* h)
{
    (void)h;
    return -1;
}

error_t logr_seek(void* h, storage_cookie_t offset)
{
    (void)h;
    (void)offset;
    return EBUSY;
}

storage_len_t logr_getSize(void* h)
{
    return (unsigned)-1;
}

static void* run(void* h)
{
	DEBUGOUT("%p: logr__run", h);
    HANDLE;
    os_sem_down();
    LOCK;
    while(1) {
        if (handle->shared.buf == NULL) {
            DEBUGOUT("%p: logr__run: i'm waiting...", h);
            WAIT;
            DEBUGOUT("%p: logr__run: i woke up", h);
        }
        assert (handle->shared.buf);

        int fd = handle->shared.fd;
        void* buf = handle->shared.buf;
        uint8_t len = handle->shared.len;
		handle->shared.buf = NULL;
		UNLOCK;

        size_t res = hs_read(fd, (unsigned char*)buf, len);

		LOCK;
		cb_lock_acquire();
		handle->callback->readDone(handle, buf, res, SUCCESS);
		cb_lock_release();
	}
	UNLOCK;
	return NULL;
}

