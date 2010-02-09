#include "os.h"
#include "cb_lock.h"
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void os_init()
{
    cb_lock_init();
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

void os_run()
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex); 
    pthread_mutex_unlock(&mutex);
}

void os_shutdown()
{
    pthread_cond_signal(&cond);
}
