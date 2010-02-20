#include "collect.h"
#include "log.h"
#include "Sensor.h"
#include "LogWrite.h"
#include "Timer.h"
#include "infra/debug.h"

void collect_run(const char* sensor, const char* file, unsigned dt)
{
    void* sensor_handle = sensor_wire(sensor);
    void* logw_handle = logw_wire(file);
	void* timer_handle = timer_wire();

    uint64_t now = timer_getNow(timer_handle);
    while (TRUE) {
        timer_sleep(timer_handle, now + dt);
        now += dt;

        sensor_val_t val;
		error_t res = sensor_read(sensor_handle, &val);
		assert (res == SUCCESS);

        log_to(logw_handle, &val, sizeof(sensor_val_t));
    }
}
