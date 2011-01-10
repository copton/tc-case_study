#ifndef SAENGIAWAIWAILIEKIMU
#define SAENGIAWAIWAILIEKIMU

typedef struct {
    void* label;
    void* stack;
} ec_continuation_t;

void RUN_THREAD(ec_continuation_t start_function); 

#endif
