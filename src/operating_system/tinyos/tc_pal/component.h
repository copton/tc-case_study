#ifndef AJOHCHOHCHISHEISHEAL
#define AJOHCHOHCHISHEISHEAL

static void* handles[TC_NUMBEROF_THREADS];

static void setHandle(void* handle)
{
    handles[tc_tid] = handle;
}

static tc_tid_t findThread(void* handle)
{
	tc_tid_t i;
    for (i=0; i<TC_NUMBEROF_THREADS; i++) {
        if (handle == handles[i]) {
            handles[i] = NULL;
            return i;
        }
    }
    return invalid_tid;
}

#endif
