#ifndef AHFOSESUEPAESHEIBEIB
#define AHFOSESUEPAESHEIBEIB

#include <assert.h>

void debugout(const char* format, ...);

#ifdef DEBUG
#define DEBUGOUT debugout
#else
#define DEBUGOUT(...)
#endif

#endif
