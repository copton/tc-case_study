#ifndef AJOHCHOHCHISHEISHEAL
#define AJOHCHOHCHISHEISHEAL

#include "infra/debug.h"
#include <stdlib.h>

typedef struct {
    void* handle;
    void* stack;
} Entry;

static Entry context_store[EC_NUMBEROF_THREADS];

static void store(void* handle, void* stack)
{
    Entry* entry = context_store + ec_tid();
    assert (entry->handle == NULL);
    entry->handle = handle;
    entry->stack = stack;
}

static void* load(void* handle)
{
    for (ec_tid_t i=0; i<EC_NUMBEROF_THREADS; i++) {
        if (handle == context_store[i].handle) {
            ec_set_tid(i);
            context_store[i].handle = NULL;
            return context_store[i].stack;
        }
    }
    return NULL;
}

#endif
