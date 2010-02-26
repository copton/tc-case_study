#ifndef THEYEILOCETUUNGOOJAA
#define THEYEILOCETUUNGOOJAA

void run_collect();
void run_receive();
void run_send();

typedef enum {
    EC_TID_COLLECT = 0,
    EC_TID_RECEIVE,
    EC_TID_SEND
} threads;

#endif
