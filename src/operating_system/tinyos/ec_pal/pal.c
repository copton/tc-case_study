#include "Pal.h"
#include "raw/Os.h"
#include "timer_init.h"

void pal_init()
{
	os_init();
    timer_init();
}

void pal_run()
{
	os_run();
}
