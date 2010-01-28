#ifndef EEVAIMAEKEEMEIBIETAE
#define EEVAIMAEKEEMEIBIETAE

typedef struct {
    int dt_collect;
    int dt_receive;
    int dt_send;
    char* fn_receive;
    char* fn_send;
    char* fn_collect;
    char* fn_flash;
} Config;

const Config* parseOptions(int argc, char** argv);


#endif
