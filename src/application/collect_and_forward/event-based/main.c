#include "os.h"
#include "receive.h"

int main()
{
    os_init();
    receive_init();
    os_run();

	return 0;
}
