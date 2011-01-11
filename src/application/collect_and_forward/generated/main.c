#include "main.h"
#include "tstack.h"
#include "Pal.h"
#include <assert.h>
#include "compiler/ec.h"

ec_stack_8 tstack_3;

int argc;
char** argv;

int main(int _argc, char** _argv)
{
    argc = _argc;
    argv = _argv;

	pal_init();
	/* EC_RUN_THREAD(&ec_stack_XX); */
	/* EC_RUN_THREAD(&ec_stack_XX); */
    EC_RUN_THREAD(&tstack_3);
    pal_run();

    assert (false);
    return 1;
}
