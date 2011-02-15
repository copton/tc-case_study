void collect_run(const char * sensor,
                 const char * file,
                 unsigned dt);
typedef unsigned storage_cookie_t;
typedef unsigned storage_len_t;
void log_to(void * handle, void * buf, storage_len_t len);
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long int uint_least64_t;
typedef signed char int_fast8_t;
typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
typedef enum {
            SUCCESS = 0,
            FAIL = 1,
            ESIZE = 2,
            ECANCEL = 3,
            EOFF = 4,
            EBUSY = 5,
            EINVAL = 6,
            ERETRY = 7,
            ERESERVE = 8,
            EALREADY = 9,
            ENOMEM = 10,
            ENOACK = 11,
            ELAST = 11
        } error_t;
typedef uint32_t sensor_val_t;
typedef struct {
            void (* readDone)(void * handle, error_t result, sensor_val_t val);
        } sensor_Callback;
void * sensor_wire(sensor_Callback * callback,
                   const char * device);
error_t sensor_read(void * handle);
typedef struct {
            void (* appendDone)(void * handle,
                                void * buf,
                                storage_len_t len,
                                _Bool recordsLost,
                                error_t error);
            void (* eraseDone)(void * handle, error_t error);
            void (* syncDone)(void * handle, error_t error);
        } logw_Callback;
void * logw_wire(logw_Callback * callback, const char * file);
error_t logw_append(void * handle, void * buf, storage_len_t len);
storage_cookie_t logw_currentOffset(void * handle);
error_t logw_erase(void * handle);
error_t logw_sync(void * handle);
typedef struct {
            void (* fired)(void * handle);
        } timer_Callback;
void * timer_wire(timer_Callback * callback);
void timer_startPeriodic(void * handle, uint32_t dt);
void timer_startOneShot(void * handle, uint32_t dt);
void timer_stop(void * handle);
_Bool timer_isRunning(void * handle);
_Bool timer_isOneShot(void * handle);
void timer_startPeriodicAt(void * handle,
                           uint32_t t0,
                           uint32_t dt);
void timer_startOneShotAt(void * handle, uint32_t t0, uint32_t dt);
uint32_t timer_getNow(void * handle);
uint32_t timer_gett0(void * handle);
uint32_t timer_getdt(void * handle);
typedef long unsigned int size_t;
typedef int wchar_t;
typedef struct {
            int quot; int rem;
        } div_t;
typedef struct {
            long int quot; long int rem;
        } ldiv_t;
typedef struct {
            long long int quot; long long int rem;
        } lldiv_t;
extern size_t __ctype_get_mb_cur_max(void) __attribute__((__nothrow__));
extern double atof(const char * __nptr) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern int atoi(const char * __nptr) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern long int atol(const char * __nptr) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern long long int atoll(const char * __nptr) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern double strtod(const char * __restrict __nptr,
                     char * * __restrict __endptr) __attribute__((__nothrow__,__nonnull__(1)));
extern float strtof(const char * __restrict __nptr,
                    char * * __restrict __endptr) __attribute__((__nothrow__,__nonnull__(1)));
extern long double strtold(const char * __restrict __nptr,
                           char * * __restrict __endptr) __attribute__((__nothrow__,__nonnull__(1)));
extern long int strtol(const char * __restrict __nptr,
                       char * * __restrict __endptr,
                       int __base) __attribute__((__nothrow__,__nonnull__(1)));
extern unsigned long int strtoul(const char * __restrict __nptr,
                                 char * * __restrict __endptr,
                                 int __base) __attribute__((__nothrow__,__nonnull__(1)));
extern long long int strtoll(const char * __restrict __nptr,
                             char * * __restrict __endptr,
                             int __base) __attribute__((__nothrow__,__nonnull__(1)));
extern unsigned long long int strtoull(const char * __restrict __nptr,
                                       char * * __restrict __endptr,
                                       int __base) __attribute__((__nothrow__,__nonnull__(1)));
extern int rand(void) __attribute__((__nothrow__));
extern void srand(unsigned int __seed) __attribute__((__nothrow__));
extern void * malloc(size_t __size) __attribute__((__nothrow__,__malloc__));
extern void * calloc(size_t __nmemb,
                     size_t __size) __attribute__((__nothrow__,__malloc__));
extern void * realloc(void * __ptr,
                      size_t __size) __attribute__((__nothrow__,__warn_unused_result__));
extern void free(void * __ptr) __attribute__((__nothrow__));
extern void abort(void) __attribute__((__nothrow__,__noreturn__));
extern int atexit(void (* __func)(void)) __attribute__((__nothrow__,__nonnull__(1)));
extern void exit(int __status) __attribute__((__nothrow__,__noreturn__));
extern void _Exit(int __status) __attribute__((__nothrow__,__noreturn__));
extern char * getenv(const char * __name) __attribute__((__nothrow__,__nonnull__(1)));
extern char * __secure_getenv(const char * __name) __attribute__((__nothrow__,__nonnull__(1)));
extern int system(const char * __command);
typedef int (* __compar_fn_t)(const void *, const void *);
extern void * bsearch(const void * __key,
                      const void * __base,
                      size_t __nmemb,
                      size_t __size,
                      __compar_fn_t __compar) __attribute__((__nonnull__(1, 2, 5)));
extern void qsort(void * __base,
                  size_t __nmemb,
                  size_t __size,
                  __compar_fn_t __compar) __attribute__((__nonnull__(1, 4)));
extern int abs(int __x) __attribute__((__nothrow__,const));
extern long int labs(long int __x) __attribute__((__nothrow__,const));
extern long long int llabs(long long int __x) __attribute__((__nothrow__,const));
extern div_t div(int __numer,
                 int __denom) __attribute__((__nothrow__,const));
extern ldiv_t ldiv(long int __numer,
                   long int __denom) __attribute__((__nothrow__,const));
extern lldiv_t lldiv(long long int __numer,
                     long long int __denom) __attribute__((__nothrow__,const));
extern int mblen(const char * __s,
                 size_t __n) __attribute__((__nothrow__));
extern int mbtowc(wchar_t * __restrict __pwc,
                  const char * __restrict __s,
                  size_t __n) __attribute__((__nothrow__));
extern int wctomb(char * __s,
                  wchar_t __wchar) __attribute__((__nothrow__));
extern size_t mbstowcs(wchar_t * __restrict __pwcs,
                       const char * __restrict __s,
                       size_t __n) __attribute__((__nothrow__));
extern size_t wcstombs(char * __restrict __s,
                       const wchar_t * __restrict __pwcs,
                       size_t __n) __attribute__((__nothrow__));
extern void __assert_fail(const char * __assertion,
                          const char * __file,
                          unsigned int __line,
                          const char * __function) __attribute__((__nothrow__,__noreturn__));
extern void __assert_perror_fail(int __errnum,
                                 const char * __file,
                                 unsigned int __line,
                                 const char * __function) __attribute__((__nothrow__,__noreturn__));
extern void __assert(const char * __assertion,
                     const char * __file,
                     int __line) __attribute__((__nothrow__,__noreturn__));
void debugout(const char * format, ...);
void collect_run(const char * sensor,
                 const char * file,
                 unsigned dt)
{
    void * sensor_handle = sensor_wire(sensor);
    void * logw_handle = logw_wire(file);
    void * timer_handle = timer_wire();
    uint32_t now = timer_getNow(timer_handle);
    while (1)
    {
        timer_sleep(timer_handle, now + dt);
        now += dt;
        sensor_val_t val;
        error_t res = sensor_read(sensor_handle, &val);
        res == SUCCESS ? (void) 0 : __assert_fail("res == SUCCESS",
                                                  "../tc-based/app.c",
                                                  21,
                                                  __PRETTY_FUNCTION__);
        log_to(logw_handle, &val, sizeof(sensor_val_t));
    }
}
void log_to(void * handle, void * buf, storage_len_t len)
{
    storage_len_t res_len;
    _Bool recordsLost;
    error_t res = logw_append(handle,
                              buf,
                              len,
                              &res_len,
                              &recordsLost);
    res == SUCCESS ? (void) 0 : __assert_fail("res == SUCCESS",
                                              "../tc-based/app.c",
                                              35,
                                              __PRETTY_FUNCTION__);
    res_len == len ? (void) 0 : __assert_fail("res_len == len",
                                              "../tc-based/app.c",
                                              36,
                                              __PRETTY_FUNCTION__);
}
void send_run(const char * channel,
              const char * file1,
              const char * file2,
              unsigned dt);
void receive_run(const char * channel, const char * file);
const char * fn_receive = "/tmp/tc/receive.sock";
const char * fn_send = "/tmp/tc/send.sock";
const char * fn_collect = "/tmp/tc/collect.sock";
const char * fn_flash_receive_source = "/tmp/tc/flash-receive-source.sock";
const char * fn_flash_collect_source = "/tmp/tc/flash-collect-source.sock";
const char * fn_flash_receive_sink = "/tmp/tc/flash-receive-sink.sock";
const char * fn_flash_collect_sink = "/tmp/tc/flash-collect-sink.sock";
const int dt_collect = 500;
const int dt_send = 2000;
__attribute__((tc_run_thread)) void run_send()
{
    send_run(fn_send,
             fn_flash_receive_source,
             fn_flash_collect_source,
             dt_send);
    0 ? (void) 0 : __assert_fail("0",
                                 "../tc-based/app.c",
                                 49,
                                 __PRETTY_FUNCTION__);
}
__attribute__((tc_run_thread)) void run_receive()
{
    receive_run(fn_receive, fn_flash_receive_sink);
    0 ? (void) 0 : __assert_fail("0",
                                 "../tc-based/app.c",
                                 55,
                                 __PRETTY_FUNCTION__);
}
__attribute__((tc_run_thread)) void run_collect(int argc,
                                                char * * argv)
{
    (void) argc;
    (void) argv;
    collect_run(fn_collect, fn_flash_collect_sink, dt_collect);
    0 ? (void) 0 : __assert_fail("0",
                                 "../tc-based/app.c",
                                 63,
                                 __PRETTY_FUNCTION__);
}
typedef struct {
            unsigned char buffer[50];
        } net_message_t;
typedef struct {
            net_message_t * (* receive)(void * handle,
                                        net_message_t * msg,
                                        void * payload,
                                        uint8_t len);
        } receive_Callback;
void * receive_wire(receive_Callback * callback,
                    const char * channel);
void receive_run(const char * channel, const char * file)
{
    void * receive_handle = receive_wire(channel);
    void * logw_handle = logw_wire(file);
    while (1)
    {
        net_message_t msg;
        void * payload;
        uint8_t len;
        error_t res = receive_receive(receive_handle,
                                      &msg,
                                      &payload,
                                      &len);
        res == SUCCESS ? (void) 0 : __assert_fail("res == SUCCESS",
                                                  "../tc-based/app.c",
                                                  81,
                                                  __PRETTY_FUNCTION__);
        log_to(logw_handle, payload, len);
    }
}
typedef struct {
            void (* readDone)(void * handle,
                              void * buf,
                              storage_len_t len,
                              error_t error);
            void (* seekDone)(void * handle, error_t error);
        } logr_Callback;
void * logr_wire(logr_Callback * callback, const char * file);
error_t logr_read(void * handle, void * buf, storage_len_t len);
storage_cookie_t logr_currentOffset(void * handle);
error_t logr_seek(void * handle, storage_cookie_t offset);
storage_len_t logr_getSize(void * handle);
typedef struct {
            void (* sendDone)(void * handle,
                              net_message_t * msg,
                              error_t error);
        } send_Callback;
void * send_wire(send_Callback * callback, const char * channel);
error_t send_send(void * handle, net_message_t * msg, uint8_t len);
error_t send_cancel(void * handle, net_message_t * msg);
uint8_t send_maxPayloadLength(void * handle);
void * send_getPayload(void * handle,
                       net_message_t * msg,
                       uint8_t len);
extern void * memcpy(void * __restrict __dest,
                     const void * __restrict __src,
                     size_t __n) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern void * memmove(void * __dest,
                      const void * __src,
                      size_t __n) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern void * memset(void * __s,
                     int __c,
                     size_t __n) __attribute__((__nothrow__,__nonnull__(1)));
extern int memcmp(const void * __s1,
                  const void * __s2,
                  size_t __n) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern void * memchr(const void * __s,
                     int __c,
                     size_t __n) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern char * strcpy(char * __restrict __dest,
                     const char * __restrict __src) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern char * strncpy(char * __restrict __dest,
                      const char * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern char * strcat(char * __restrict __dest,
                     const char * __restrict __src) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern char * strncat(char * __restrict __dest,
                      const char * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int strcmp(const char * __s1,
                  const char * __s2) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern int strncmp(const char * __s1,
                   const char * __s2,
                   size_t __n) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern int strcoll(const char * __s1,
                   const char * __s2) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern size_t strxfrm(char * __restrict __dest,
                      const char * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__nonnull__(2)));
extern char * strchr(const char * __s,
                     int __c) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern char * strrchr(const char * __s,
                      int __c) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern size_t strcspn(const char * __s,
                      const char * __reject) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern size_t strspn(const char * __s,
                     const char * __accept) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern char * strpbrk(const char * __s,
                      const char * __accept) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern char * strstr(const char * __haystack,
                     const char * __needle) __attribute__((__nothrow__,__pure__,__nonnull__(1, 2)));
extern char * strtok(char * __restrict __s,
                     const char * __restrict __delim) __attribute__((__nothrow__,__nonnull__(2)));
extern char * __strtok_r(char * __restrict __s,
                         const char * __restrict __delim,
                         char * * __restrict __save_ptr) __attribute__((__nothrow__,__nonnull__(2, 3)));
extern size_t strlen(const char * __s) __attribute__((__nothrow__,__pure__,__nonnull__(1)));
extern char * strerror(int __errnum) __attribute__((__nothrow__));
extern void __bzero(void * __s,
                    size_t __n) __attribute__((__nothrow__,__nonnull__(1)));
static void aggregate_from(void * handle,
                           int32_t * min,
                           int32_t * max)
{
    unsigned char read_buffer[50];
    storage_len_t len;
    error_t res = logr_read(handle,
                            read_buffer,
                            sizeof(read_buffer),
                            &len);
    res == SUCCESS ? (void) 0 : __assert_fail("res == SUCCESS",
                                              "../tc-based/app.c",
                                              99,
                                              __PRETTY_FUNCTION__);
    len % sizeof(int32_t) == 0 ? (void) 0 : __assert_fail("(len % sizeof(int32_t)) == 0",
                                                          "../tc-based/app.c",
                                                          100,
                                                          __PRETTY_FUNCTION__);
    {
        int i;
        for (i = 0; i < len / sizeof(int32_t); i++)
        {
            int32_t tmp;
            memcpy(&tmp, read_buffer + i * sizeof(int32_t), sizeof(int32_t));
            if (tmp < *min)
            {
                *min = tmp;
            }
            if (tmp > *max)
            {
                *max = tmp;
            }
        }
    }
}
static void send_via(void * handle, int32_t min, int32_t max)
{
    net_message_t msg;
    void * payload = send_getPayload(handle,
                                     &msg,
                                     2 * sizeof(int32_t));
    memcpy(payload, &min, sizeof(int32_t));
    memcpy(payload + sizeof(int32_t), &max, sizeof(int32_t));
    error_t res = send_send(handle, &msg, 2 * sizeof(int32_t));
    res == SUCCESS ? (void) 0 : __assert_fail("res == SUCCESS",
                                              "../tc-based/app.c",
                                              120,
                                              __PRETTY_FUNCTION__);
}
void send_run(const char * channel,
              const char * file1,
              const char * file2,
              unsigned dt)
{
    void * logr1_handle = logr_wire(file1);
    void * logr2_handle = logr_wire(file2);
    void * send_handle = send_wire(channel);
    void * timer_handle = timer_wire();
    uint32_t now = timer_getNow(timer_handle);
    while (1)
    {
        timer_sleep(timer_handle, now + dt);
        now += dt;
        int32_t min = 0x7fffffff;
        int32_t max = 0xffffffff;
        aggregate_from(logr1_handle, &min, &max);
        aggregate_from(logr2_handle, &min, &max);
        send_via(send_handle, min, max);
    }
}
