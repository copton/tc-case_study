#ifndef SAENGIAWAIWAILIEKIMU
#define SAENGIAWAIWAILIEKIMU

typedef int ec_tid_t;
#define ec_invalid_tid -1

extern ec_tid_t the_tid;
#define ec_tid() the_tid
#define ec_set_tid(tid) the_tid=tid

//ec_tid_t ec_tid();
//void ec_set_tid(ec_tid_t tid);

typedef void (*ec_continuation_t)();

void RUN_THREAD(ec_continuation_t start_function); 

#endif
