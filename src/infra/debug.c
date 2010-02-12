#include <stdarg.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "error.h"

static pthread_mutex_t mutex;

void debug_init()
{
    pthread_mutex_init(&mutex, NULL);
}

void debugout(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    time_t now = time(NULL);
    pthread_t id = pthread_self();

    if (pthread_mutex_lock(&mutex) != 0) { 
        errorExit("lock"); 
    }

    printf("%lu: %lu: ", now, id);
    vprintf(format, ap);
    printf("\n");
	fflush(stdout);

    if (pthread_mutex_unlock(&mutex) != 0) { 
        errorExit("lock"); 
    }
    va_end(ap);
}