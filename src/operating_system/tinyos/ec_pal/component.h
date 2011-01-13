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
    Entry* entry = &context_store[ec_tid()-1];
    assert (entry->handle == NULL);
    entry->handle = handle;
    entry->stack = stack;
//    DEBUGOUT("%d: storing %x -> %x [%x]", ec_tid(), handle, stack, context_store);
}

static void* load(void* handle)
{
    for (ec_tid_t i=0; i<EC_NUMBEROF_THREADS; i++) {
        if (handle == context_store[i].handle) {
            ec_set_tid(i+1);
            context_store[i].handle = NULL;
//            DEBUGOUT("%d: loading %x -> %x [%x]", ec_tid(), handle, context_store[i].stack, context_store);
            return context_store[i].stack;
        }
    }
//    DEBUGOUT("%d: loading %x -> NULL [%x]", ec_tid(), handle, context_store);
    return NULL;
}

#endif
