#ifndef AHFOSESUEPAESHEIBEIB
#define AHFOSESUEPAESHEIBEIB

void debugout(const char* format, ...);

#ifdef DEBUG
#define DEBUGOUT debugout
#else
#define DEBUGOUT(...)
#endif

#endif
