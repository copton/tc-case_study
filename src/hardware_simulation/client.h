#ifndef GIEKOHGOOSHAOXUXEIRO
#define GIEKOHGOOSHAOXUXEIRO

#include <stdlib.h>

int hs_open(const char* path);
void hs_close(int fd);
void hs_send(int fd, unsigned* data, size_t len);
size_t hs_receive(int fd, unsigned* data, size_t len);

#endif
