#ifndef AJOHCHOHCHISHEISHEAL
#define AJOHCHOHCHISHEISHEAL

static void* handles[TC_NUMBEROF_THREADS];

static tid_t findThread(void* handle)
{
	tid_t i;
    for (i=0; i<TC_NUMBEROF_THREADS; i++) {
        if (handle == handles[i]) {
            return i;
        }
    }
    assert (FALSE);
}

#endif
