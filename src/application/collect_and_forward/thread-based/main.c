#include <pthread.h>
#include "send.h"
#include "receive.h"
#include "collect.h"
#include "infra/types.h"
#include "infra/debug.h"
#include "config.h"

static void* run_send(void* args)
{
	(void)args;
	send_run(fn_send, fn_flash_receive_source, fn_flash_collect_source, dt_send);
	assert (false);
	return NULL;
}

static void* run_receive(void* args)
{
	(void)args;
	receive_run(fn_receive, fn_flash_receive_sink);
	assert (false);
	return NULL;
}

static void* run_collect(void* args)
{
	(void)args;
	collect_run(fn_collect, fn_flash_collect_sink, dt_collect);
	assert (false);
	return NULL;
}

int main()
{
	pthread_t send_thread;
	pthread_t receive_thread;
	pthread_t collect_thread;
	
	pthread_create(&send_thread, NULL, run_send, NULL);
	pthread_create(&receive_thread, NULL, run_receive, NULL);
	pthread_create(&collect_thread, NULL, run_collect, NULL);

	pthread_cond_t cond;
	pthread_mutex_t mutex;
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	while(1) {
		pthread_cond_wait(&cond, &mutex);
	}

	return 0;
}
