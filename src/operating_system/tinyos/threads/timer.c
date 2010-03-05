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

static uint64_t getNow()
{
    struct timeval tv;
	{
		int res = gettimeofday(&tv, NULL);
		if (res == -1) {
			errorExit("gettimeofday");
		}
	}
	uint64_t res = tv.tv_sec * 1000;
	res += tv.tv_usec / 1000;
    return res;
}

error_t timer_sleep(void* h, uint32_t until)
{
    HANDLE;
    ENTER;

	uint64_t now = getNow();	
    uint32_t diff;
    if (until > now) {
        diff = until - now;
    } else {
        diff = until + (0xFFFFFFFFFFFFFFFFull - now);
    }
    struct timespec req = { diff / 1000, (diff % 1000) * 1000 * 1000 };
    int res = nanosleep(&req, NULL);
    if (res != 0) {
        errorExit("nanosleep");
    }

    LEAVE;
    return SUCCESS;
}

uint32_t timer_getNow(void* h)
{
    return getNow();
}
