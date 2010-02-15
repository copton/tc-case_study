#include "Timer.h"
#include "time.h"
#include <assert.h>
#include <errno.h>
#include "infra/error.h"

#include <time.h>
#include <sys/time.h>

void timer_sleep(uint64_t until)
{
	uint64_t now = timer_getNow();	
	assert (now < until);
	uint64_t diff = until - now;
	struct timespec req = { diff / 1000, (diff % 1000) * 1000 * 1000 };
	int res = nanosleep(&req, NULL);
	if (res != 0) {
		errorExit("nanosleep");
	}
}

uint64_t timer_getNow()
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
