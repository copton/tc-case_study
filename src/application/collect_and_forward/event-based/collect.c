#include "collect.h"

#include "Timer.h"
#include "Sensor.h"
#include "LogWrite.h"

#include "infra/debug.h"

#include <stddef.h>

static void* timer_handle = NULL;
static void* sensor_handle = NULL;
static void* logw_handle = NULL;

typedef enum {
	WAIT_TIMER,
	WAIT_READ,
	WAIT_LOG,
} State;

static State state;

static sensor_val_t cur_value;

static void fired(void* handle)
{
	DEBUGOUT("collect__fired(%p)", handle);
	assert (state == WAIT_TIMER);
    assert (handle == timer_handle);

    error_t res = sensor_read(sensor_handle); (void)res;
    assert (res == SUCCESS);

	state = WAIT_READ;
}

static void readDone(void* handle, error_t error, sensor_val_t value)
{
    DEBUGOUT("collect__readDone(%p, %d, %d)", handle, error, value);
	assert (state == WAIT_READ);
	assert (error == SUCCESS);
	
	cur_value = value;

	error_t res = logw_append(logw_handle, &cur_value, sizeof(sensor_val_t));
	assert (res == SUCCESS); (void)res;

	state = WAIT_LOG;
}

static void appendDone(void* handle, void* buf, storage_len_t len, bool recordsLost, error_t error)
{
    DEBUGOUT("collect__appendDone(%p, %p, %u, %d, %d)", handle, buf, len, recordsLost, error);
	assert (state == WAIT_LOG);
	assert (handle == logw_handle);
	assert (buf == &cur_value);
	assert (len == sizeof(sensor_val_t));
	(void)recordsLost;
	assert (error == SUCCESS);

	state = WAIT_TIMER;
}

static timer_Callback timer_callback = {&fired};
static sensor_Callback sensor_callback = {&readDone};
static logw_Callback logw_callback = {&appendDone, NULL};

void collect_init(const char* sensor, const char* file, unsigned dt)
{
	DEBUGOUT("collect_init(%s, %s)", sensor, file);
    timer_handle = timer_wire(&timer_callback);
    sensor_handle = sensor_wire(&sensor_callback, sensor);
	logw_handle = logw_wire(&logw_callback, file);
	state = WAIT_TIMER;
    timer_startPeriodic(timer_handle, dt);
}
