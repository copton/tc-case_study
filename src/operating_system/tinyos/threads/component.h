#ifndef EZEIWOOVUPAHVAOJAIBA
#define EZEIWOOVUPAHVAOJAIBA

#include <pthread.h>
#include "infra/types.h"
#include "infra/error.h"

typedef struct {
    pthread_mutex_t mutex;
    bool busy;
} Thread;

typedef struct {
    Thread thread;
    State state;
} Handle;

#define HANDLE Handle* handle = (Handle*)h
#define ENTER do { \
    if (pthread_mutex_lock(&handle->thread.mutex) != 0) { \
        errorExit("mutex_lock"); \
    } \
    if (handle->thread.busy) return EBUSY; \
    handle->thread.busy = TRUE; \
} while (0)

#define LEAVE do { \
    if (pthread_mutex_unlock(&handle->thread.mutex) != 0) { \
        errorExit("mutex_unlock"); \
    } \
    handle->thread.busy = FALSE; \
} while (0)

static void setupThread(Handle* handle)
{
    pthread_mutex_init(&handle->thread.mutex, NULL);
    handle->thread.busy = FALSE;
}

#endif
