typedef struct {

} State;

#include "component.h"

#include "Timer.h"
#include <errno.h>

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

void* timer_wire()
{
    Handle* handle = malloc(sizeof(Handle));
    setupThread(handle);
    return handle;
}

error_t timer_sleep(void* h, uint64_t until)
{
    HANDLE;
    ENTER;

	uint64_t now = timer_getNow(h);	
	assert (now < until);
	uint64_t diff = until - now;
	struct timespec req = { diff / 1000, (diff % 1000) * 1000 * 1000 };
	int res = nanosleep(&req, NULL);
	if (res != 0) {
		errorExit("nanosleep");
	}

    LEAVE;
    return SUCCESS;
}

uint64_t timer_getNow(void* h)
{
    struct timeval tv;
	{
		int res = gettimeofday(&tv, NULL);
		if (res == -1) {
			errorExit("gettimeofday");
		}
	}
	uint32_t res = tv.tv_sec * 1000;
	res += tv.tv_usec / 1000;
    return res;
}
