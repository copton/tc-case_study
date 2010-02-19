#ifndef AJOHCHOHCHISHEISHEAL
#define AJOHCHOHCHISHEISHEAL

#include "infra/debug.h"
#include <stdlib.h>

static void* handles[TC_NUMBEROF_THREADS];

static void setHandle(void* handle)
{
    assert(handles[ec_tid()] == NULL);
    handles[ec_tid()] = handle;
}

static ec_tid_t findThread(void* handle)
{
	ec_tid_t i;
    for (i=0; i<TC_NUMBEROF_THREADS; i++) {
        if (handle == handles[i]) {
            handles[i] = NULL;
            return i;
        }
    }
    return ec_invalid_tid;
}

#endif
