#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


#include "lib/error.h"

int hs_open(const char* path)
{
    struct sockaddr_un strAddr;
    socklen_t lenAddr;
    int fd;
    if ((fd=socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
        errorExit("socket");

    strAddr.sun_family=AF_UNIX;
    strcpy(strAddr.sun_path, path);
    lenAddr=sizeof(strAddr.sun_family)+strlen(strAddr.sun_path);
    if (connect(fd, (struct sockaddr*)&strAddr, lenAddr) !=0 )
        errorExit("connect");

    return fd;
}

void hs_close(int fd)
{
    close(fd);
}

void hs_send(int fd, unsigned* data, size_t len)
{
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

void hs_receive(int fd, unsigned** data, size_t* len)
{
    const char next[] = "next";
    hs_send(fd, (unsigned*)next, sizeof(next));

    size_t bufsize = 512;
    unsigned* buffer = malloc(bufsize);
    //TODO grow receive buffer if message is longer
    while(1) {
        ssize_t res = recv(fd, (void*) buffer, bufsize, 0);
        if (res == -1) {
            if (errno == EINTR) {
                continue;
            }
        }
        *len = res;
        *data = buffer;
        return;
    }
}


