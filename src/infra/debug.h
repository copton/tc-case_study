#ifndef AHFOSESUEPAESHEIBEIB
#define AHFOSESUEPAESHEIBEIB

#include <stdlib.h>
#include <assert.h>

void debugout(const char* format, ...);

#ifdef NDEBUG
#define DEBUGOUT(...)
#else
#define DEBUGOUT debugout
#endif

#endif
