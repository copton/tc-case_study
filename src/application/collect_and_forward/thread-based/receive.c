#include "receive.h"
#include "LogWrite.h"
#include "Receive.h"
#include <assert.h>

void receive_run(const char* channel, const char* file)
{
    void* receive_handle = receive_wire(channel);
    void* logw_handle = logw_wire(file);
    while (TRUE) {
        net_message_t msg;
        unsigned char* payload;
        uint8_t len;

        {
            error_t res = receive_receive(receive_handle, &msg, (void**)&payload, &len);
            assert (res == SUCCESS);
        }

        {
            storage_len_t res_len;
            bool recordsLost;
            error_t res = logw_append(logw_handle, payload, len, &res_len, &recordsLost);
            assert (res == SUCCESS);
            assert (res_len == len);
        }
    }
}
