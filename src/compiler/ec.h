#ifndef SAENGIAWAIWAILIEKIMU
#define SAENGIAWAIWAILIEKIMU

typedef struct {
    void* label;
    void* stack;
} ec_continuation_t;

void ec_events(ec_continuation_t cont);

typedef int ec_tid_t;
ec_tid_t ec_tid();
void ec_set_tid(ec_tid_t);

void EC_RUN_THREAD(void* stack);

#endif
