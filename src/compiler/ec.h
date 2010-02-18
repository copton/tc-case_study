#ifndef SAENGIAWAIWAILIEKIMU
#define SAENGIAWAIWAILIEKIMU

typedef int ec_tid_t;
#define invalid_tid -1

ec_tid_t ec_tid();
void ec_set_tid(ec_tid_t tid);

typedef void (*ec_continuation_t)();

void RUN_THREADS(int numberof_threads, ...); // list of ec_continuation_t

#endif
