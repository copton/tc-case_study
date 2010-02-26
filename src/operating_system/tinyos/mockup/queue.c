#include "Queue.h"

static q_Handler current;

void q_push(q_Handler handler)
{
    current = handler;
}

void q_next()
{
    current();
}
