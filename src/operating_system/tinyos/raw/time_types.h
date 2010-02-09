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

inline RelTime rt_create(uint32_t t) 
{
    RelTime res = {t};
    return res;
}

inline uint32_t rt_unpack(RelTime in)
{
    return in.t;
}

inline RelTime at_to_rt(AbsTime in)
{
    RelTime out = { (uint32_t) in.t };
    return out;
}

inline AbsTime at_getFrame(AbsTime in)
{
	AbsTime out = { (in.t & 0xFFFFFFFF00000000L) };
	return out;
}

inline AbsTime at_prevFrame(AbsTime in)
{
    AbsTime out = { in.t - 0xFFFFFFFF };
    return out;
}

inline AbsTime at_create(struct timeval tv)
{
    AbsTime res;
    res.t = tv.tv_sec;
    res.t *= 1000;
    res.t += tv.tv_usec / 1000;
    return res;
}

inline bool rt_le(RelTime lhs, RelTime rhs)
{
    return lhs.t <= rhs.t;
}

inline AbsTime at_plus(AbsTime lhs, RelTime rhs)
{
    AbsTime res = {lhs.t + rhs.t};
    return res;
}

inline RelTime rt_plus(RelTime lhs, RelTime rhs)
{
    RelTime res = {lhs.t + rhs.t};
    return res;
}

inline uint64_t at_unpack(AbsTime in)
{
    return in.t;
}

#endif
