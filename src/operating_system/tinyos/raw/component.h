#ifndef FEIYEEPHAHCHAIFIEQUI
#define FEIYEEPHAHCHAIFIEQUI

#include "infra/error.h"
#include "infra/debug.h"
#include "cb_lock.h"
#include "os.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    pthread_t thread;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} Thread;

typedef struct {
    Callback* callback;
    Shared shared;
    Thread thread;
} Handle;

#define LOCK if (pthread_mutex_lock(&handle->thread.mutex) != 0) { errorExit("mutex_lock"); }
#define UNLOCK if (pthread_mutex_unlock(&handle->thread.mutex) != 0) { errorExit("mutex unlock"); }
#define SIGNAL if (pthread_cond_signal(&handle->thread.cond) != 0) { errorExit("cond_signal"); }
#define WAIT if (pthread_cond_wait(&handle->thread.cond, &handle->thread.mutex) != 0) { errorExit("cond_wait"); }
#define HANDLE Handle* handle = (Handle*)h;

static void* run(void* handle);

static void setupThread(Handle* handle)
{
    pthread_cond_init(&handle->thread.cond, NULL);
    pthread_mutex_init(&handle->thread.mutex, NULL);
    pthread_create(&handle->thread.thread, NULL, run, handle);
    DEBUGOUT("started thread %lu", handle->thread.thread);
    os_sem_up();
}

#endif
