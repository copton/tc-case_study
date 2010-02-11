#include "cb_lock.h"

#include <pthread.h>
#include "infra/error.h"
#include "infra/debug.h"

static pthread_mutex_t mutex;

void cb_lock_init()
{
    pthread_mutex_init(&mutex, NULL);
}

void cb_lock_acquire()
{
//	DEBUGOUT("cb_lock_acquire()");
    if (pthread_mutex_lock(&mutex) != 0) 
        errorExit("lock callback mutex");
//	DEBUGOUT("cb_lock_acquire() -> ");
}

void cb_lock_release()
{
//	DEBUGOUT("cb_lock_release()");
    if (pthread_mutex_unlock(&mutex) !=0)
        errorExit("unlock callback mutex");
//	DEBUGOUT("cb_lock_release() -> ");
}
