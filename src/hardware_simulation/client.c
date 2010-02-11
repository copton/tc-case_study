#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


#include "infra/error.h"
#include "infra/debug.h"

int hs_open(const char* path)
{
    DEBUGOUT("hs_open(%s)", path);
    struct sockaddr_un strAddr;
    socklen_t lenAddr;
    int fd;
    if ((fd=socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
        errorExit("socket");
    }

    strAddr.sun_family=AF_UNIX;
    strcpy(strAddr.sun_path, path);
    lenAddr=sizeof(strAddr.sun_family)+strlen(strAddr.sun_path);
    if (connect(fd, (struct sockaddr*)&strAddr, lenAddr) !=0 )
        errorExit("connect");

    DEBUGOUT("hs_open() -> %d", fd);
    return fd;
}

void hs_close(int fd)
{
    DEBUGOUT("hs_close(%d)", fd);
    close(fd);
}

void hs_write(int fd, unsigned* data, size_t len)
{
    return hs_send(fd, data, len);
}

void hs_send(int fd, unsigned* data, size_t len)
{
    DEBUGOUT("hs_send(%d, %p, %ld)", fd, data, len);
    while(1) {
        ssize_t res = send(fd, (void*)data, len, MSG_NOSIGNAL); 
        if (res == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                errorExit("send");
            }
        } 
        assert((size_t)res == len);
        return;
    }
}

size_t hs_read(int fd, unsigned* data, size_t len)
{
    DEBUGOUT("hs_receive(%d, %p, %ld)", fd, data, len);
    const char next[] = "next";
    hs_send(fd, (unsigned*)next, sizeof(next)-1);

    return hs_receive(fd, data, len);
}

size_t hs_receive(int fd, unsigned* data, size_t len)
{
    DEBUGOUT("hs_receive(%d, %p, %ld)", fd, data, len);
    while(1) {
        ssize_t res = recv(fd, (void*) data, len, 0);
        if (res == -1) {
            if (errno == EINTR) {
                continue;
            }
        }
        return (size_t)res;
    }
}


