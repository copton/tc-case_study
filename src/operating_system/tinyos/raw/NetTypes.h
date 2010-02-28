#ifndef IEJUESOHPHUPEICHOHQU
#define IEJUESOHPHUPEICHOHQU

#ifdef BUFFER_SIZE
#define net_buffer_size BUFFER_SIZE
#else
#define net_buffer_size 50
#endif

typedef struct {
    // XXX
    unsigned char buffer[net_buffer_size];
} net_message_t;

#endif
