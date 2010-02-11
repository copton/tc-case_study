#ifndef AHFOSESUEPAESHEIBEIB
#define AHFOSESUEPAESHEIBEIB

void debug_init();
void debugout(const char* format, ...);

#ifdef DEBUG
#define DEBUGOUT debugout
#else
#define DEBUGOUT(...)
#endif

#endif
