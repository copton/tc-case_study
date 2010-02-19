#include "LogWrite.h"

typedef logw_Callback Callback;

typedef struct {
    int fd;
    void* buf;
    storage_len_t len;
} Shared;

#include "component.h"
#include "hardware_simulation/client.h"

void* logw_wire(logw_Callback* callback, const char* file)
{
	DEBUGOUT("logw_wire(%p, %s)", callback, file);
	Handle* handle = malloc(sizeof(Handle));
	handle->callback = callback;

    handle->shared.fd = hs_open(file);
    handle->shared.buf = NULL;
    handle->shared.len = 0;

    setupThread(handle);

	DEBUGOUT("logw_wire(...) -> %p", handle);
    return handle;
}

error_t logw_append(void* h, void* buf, storage_len_t len)
{
	DEBUGOUT("logw_append(%p, %p, %u)", h, buf, len);
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
	DEBUGOUT("logw_append(...) -> %d", res);
    return res;
}

storage_cookie_t logw_currentOffset(void* h)
{
    (void)h;
    return -1;
}

error_t logw_erase(void* h)
{
    (void)h;
    return EBUSY;
}

error_t logw_sync(void* h)
{
    (void)h;
    return EBUSY;
}

static void* run(void* h)
{
	DEBUGOUT("logw__run(%p)", h);
    HANDLE;
    os_sem_down();
    LOCK;
    while(1) {
		if (handle->shared.buf == NULL) {
			DEBUGOUT("logw__run i'm waiting...");
			WAIT;
			DEBUGOUT("logw__run dumdidum...");
		}
        assert (handle->shared.buf);

        int fd = handle->shared.fd;
        void* buf = handle->shared.buf;
        uint8_t len = handle->shared.len;
		handle->shared.buf = NULL;
		UNLOCK;

        hs_send(fd, (unsigned char*)buf, len);

		LOCK;
		cb_lock_acquire();
		handle->callback->appendDone(handle, buf, len, FALSE, SUCCESS);
		cb_lock_release();
	}
	UNLOCK;
	return NULL;
}
