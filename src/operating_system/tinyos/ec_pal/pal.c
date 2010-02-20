#include "Pal.h"
#include "raw/Os.h"

void pal_init()
{
	os_init();
}

void pal_run()
{
	os_run();
}
