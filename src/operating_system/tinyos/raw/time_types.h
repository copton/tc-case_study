#ifndef AIGHAIHIJEINOHHEEMIU
#define AIGHAIHIJEINOHHEEMIU

#include "infra/types.h"
#include <sys/time.h>

typedef struct {
	uint64_t t;
} AbsTime;

typedef struct {
	uint32_t t;
} RelTime;

RelTime rt_create(uint32_t t);
uint32_t rt_unpack(RelTime in);
RelTime at_to_rt(AbsTime in);
AbsTime at_getFrame(AbsTime in);
AbsTime at_prevFrame(AbsTime in);
AbsTime at_create(struct timeval tv);
bool rt_le(RelTime lhs, RelTime rhs);
AbsTime at_plus(AbsTime lhs, RelTime rhs);
RelTime rt_plus(RelTime lhs, RelTime rhs);
uint64_t at_unpack(AbsTime in);

#endif
