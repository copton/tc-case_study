#ifndef GIEKOHGOOSHAOXUXEIRO
#define GIEKOHGOOSHAOXUXEIRO

#include <stdlib.h>

int hs_open(const char* path);
void hs_close(int fd);
void hs_write(int fd, unsigned char* data, size_t len);
void hs_send(int fd, unsigned char* data, size_t len);
size_t hs_read(int fd, unsigned char* data, size_t len);
size_t hs_receive(int fd, unsigned char* data, size_t len);

#endif
