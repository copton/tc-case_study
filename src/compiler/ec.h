#ifndef SAENGIAWAIWAILIEKIMU
#define SAENGIAWAIWAILIEKIMU

typedef int ec_tid_t;
extern ec_tid_t ec_tid;
#define invalid_tid -1

typedef void (*ec_continuation_t)();

void RUN_THREADS(int numberof_threads, ...); // list of ec_continuation_t

#endif
