#include "time_types.h"

RelTime rt_create(uint32_t t) 
{
    RelTime res = {t};
    return res;
}

uint32_t rt_unpack(RelTime in)
{
    return in.t;
}

RelTime at_to_rt(AbsTime in)
{
    RelTime out = { (uint32_t) in.t };
    return out;
}

AbsTime at_getFrame(AbsTime in)
{
	AbsTime out = { (in.t & 0xFFFFFFFF00000000ull) };
	return out;
}

AbsTime at_prevFrame(AbsTime in)
{
    AbsTime out = { in.t - 0xFFFFFFFF };
    return out;
}

AbsTime at_create(struct timeval tv)
{
    AbsTime res;
    res.t = tv.tv_sec;
    res.t *= 1000;
    res.t += tv.tv_usec / 1000;
    return res;
}

bool rt_le(RelTime lhs, RelTime rhs)
{
    return lhs.t <= rhs.t;
}

AbsTime at_plus(AbsTime lhs, RelTime rhs)
{
    AbsTime res = {lhs.t + rhs.t};
    return res;
}

RelTime rt_plus(RelTime lhs, RelTime rhs)
{
    RelTime res = {lhs.t + rhs.t};
    return res;
}

uint64_t at_unpack(AbsTime in)
{
    return in.t;
}
