#include "cb_lock.h"

#include <pthread.h>
#include "lib/error.h"

pthread_mutex_t mutex;

void cb_lock_init()
{
    pthread_mutex_init(&mutex, NULL);
}

void cb_lock_acquire()
{
    if (pthread_mutex_lock(&mutex) != 0) 
        errorExit("lock callback mutex");
}

void cb_lock_release()
{
    if (pthread_mutex_unlock(&mutex) !=0)
        errorExit("unlock callback mutex");
}
