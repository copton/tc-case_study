#include "Run.h"
#include <pthread.h>

void pal_run()
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    while(1) {
        pthread_cond_wait(&cond, &mutex);
    }
}
