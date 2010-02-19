#include "Os.h"
#include "os.h"
#include "cb_lock.h"
#include <pthread.h>
#include "infra/debug.h"

static pthread_mutex_t mutex;
static pthread_cond_t cond;
static int counter;

void os_init()
{
	counter = 1;
    cb_lock_init();
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

void os_sem_up()
{
    pthread_mutex_lock(&mutex);
	counter += 1;
	pthread_mutex_unlock(&mutex);
}

void os_sem_down()
{
    pthread_mutex_lock(&mutex);
	assert(counter > 0);
	counter -= 1;
	if (counter == 0) {
		pthread_cond_broadcast(&cond);
	} else {
		while (counter != 0) {
			pthread_cond_wait(&cond, &mutex);	
		}
	}
	pthread_mutex_unlock(&mutex);
}

void os_run()
{
    DEBUGOUT("os threads starting now");
	os_sem_down();
    pthread_mutex_lock(&mutex);
	while(1) {
		pthread_cond_wait(&cond, &mutex); 
	}
}
