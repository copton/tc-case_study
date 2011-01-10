#include "main.h"
#include "Pal.h"
#include <assert.h>

int main(int _argc, char** _argv)
{
    argc = _argc;
    argv = _argv;
    ec_continuation_t continuation = {0,0};
    void* stacks[] = {&ec_tstack_1; &ec_tstack_2; &ec_tstack_3, 0};

	pal_init();
    for (tid = 0; stacks[tid] != 0; ++tid) {
        continuation.stack = stacks[tid];
        ec_events(continuation);
    }
    pal_run();

    assert (false);
    return 1;
}
