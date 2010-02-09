#include "os.h"
#include "receive.h"
#include "collect.h"

int main()
{
    os_init();
    receive_init();
    collect_init("/tmp/tc/collect.sock", "/tmp/tc/flash-collecT.SOCK"); 
    os_run();

	return 0;
}
