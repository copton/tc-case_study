#include "receive.h"
#include "log.h"
#include "LogWrite.h"
#include "Receive.h"
#include "infra/debug.h"

void receive_run(const char* channel, const char* file)
{
    void* receive_handle = receive_wire(channel);
    void* logw_handle = logw_wire(file);
    while (true) {
        net_message_t msg;
        unsigned char* payload;
        uint8_t len;

		error_t res = receive_receive(receive_handle, &msg, (void**)&payload, &len);
		assert (res == SUCCESS);

		log_to(logw_handle, payload, len);
    }
}
