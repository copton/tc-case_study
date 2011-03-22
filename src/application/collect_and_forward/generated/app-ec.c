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
void * sensor_wire(const char * device);
__attribute__((tc_blocking)) error_t sensor_read(void * handle,
                                                 sensor_val_t * val);
void * logw_wire(const char * file);
__attribute__((tc_blocking)) error_t logw_append(void * handle,
                                                 void * buf,
                                                 storage_len_t len,
                                                 storage_len_t * res_len,
                                                 _Bool * recordsLost);
storage_cookie_t logw_currentOffset(void * handle);
error_t logw_erase(void * handle);
error_t logw_sync(void * handle);
void * timer_wire();
__attribute__((tc_blocking)) error_t timer_sleep(void * handle,
                                                 uint32_t until);
uint32_t timer_getNow(void * handle);
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
                                                  "app-tc.c",
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
                                              "app-tc.c",
                                              35,
                                              __PRETTY_FUNCTION__);
    res_len == len ? (void) 0 : __assert_fail("res_len == len",
                                              "app-tc.c",
                                              36,
                                              __PRETTY_FUNCTION__);
}
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct {
            int __val[2];
        } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef long int __swblk_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __ssize_t;
typedef __off64_t __loff_t;
typedef __quad_t * __qaddr_t;
typedef char * __caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
typedef __time_t time_t;
struct timespec {
    __time_t tv_sec; long int tv_nsec;
};
typedef __pid_t pid_t;
struct sched_param {
    int __sched_priority;
};
struct __sched_param {
    int __sched_priority;
};
typedef unsigned long int __cpu_mask;
typedef struct {
            __cpu_mask __bits[1024 / (8 * sizeof(__cpu_mask))];
        } cpu_set_t;
extern int __sched_cpucount(size_t __setsize,
                            const cpu_set_t * __setp) __attribute__((__nothrow__));
extern cpu_set_t * __sched_cpualloc(size_t __count) __attribute__((__nothrow__));
extern void __sched_cpufree(cpu_set_t * __set) __attribute__((__nothrow__));
extern int sched_setparam(__pid_t __pid,
                          const struct sched_param * __param) __attribute__((__nothrow__));
extern int sched_getparam(__pid_t __pid,
                          struct sched_param * __param) __attribute__((__nothrow__));
extern int sched_setscheduler(__pid_t __pid,
                              int __policy,
                              const struct sched_param * __param) __attribute__((__nothrow__));
extern int sched_getscheduler(__pid_t __pid) __attribute__((__nothrow__));
extern int sched_yield(void) __attribute__((__nothrow__));
extern int sched_get_priority_max(int __algorithm) __attribute__((__nothrow__));
extern int sched_get_priority_min(int __algorithm) __attribute__((__nothrow__));
extern int sched_rr_get_interval(__pid_t __pid,
                                 struct timespec * __t) __attribute__((__nothrow__));
typedef __clock_t clock_t;
struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
    long int __tm_gmtoff;
    const char * __tm_zone;
};
extern clock_t clock(void) __attribute__((__nothrow__));
extern time_t time(time_t * __timer) __attribute__((__nothrow__));
extern double difftime(time_t __time1,
                       time_t __time0) __attribute__((__nothrow__,const));
extern time_t mktime(struct tm * __tp) __attribute__((__nothrow__));
extern size_t strftime(char * __restrict __s,
                       size_t __maxsize,
                       const char * __restrict __format,
                       const struct tm * __restrict __tp) __attribute__((__nothrow__));
extern struct tm * gmtime(const time_t * __timer) __attribute__((__nothrow__));
extern struct tm * localtime(const time_t * __timer) __attribute__((__nothrow__));
extern char * asctime(const struct tm * __tp) __attribute__((__nothrow__));
extern char * ctime(const time_t * __timer) __attribute__((__nothrow__));
extern char * __tzname[2];
extern int __daylight;
extern long int __timezone;
typedef unsigned long int pthread_t;
typedef union {
            char __size[56]; long int __align;
        } pthread_attr_t;
typedef struct __pthread_internal_list {
            struct __pthread_internal_list * __prev;
            struct __pthread_internal_list * __next;
        } __pthread_list_t;
typedef union {
            struct __pthread_mutex_s {
                int __lock;
                unsigned int __count;
                int __owner;
                unsigned int __nusers;
                int __kind;
                int __spins;
                __pthread_list_t __list;
            } __data;
            char __size[40];
            long int __align;
        } pthread_mutex_t;
typedef union {
            char __size[4]; int __align;
        } pthread_mutexattr_t;
typedef union {
            struct {
                int __lock;
                unsigned int __futex;
                unsigned long long int __total_seq;
                unsigned long long int __wakeup_seq;
                unsigned long long int __woken_seq;
                void * __mutex;
                unsigned int __nwaiters;
                unsigned int __broadcast_seq;
            } __data;
            char __size[48];
            long long int __align;
        } pthread_cond_t;
typedef union {
            char __size[4]; int __align;
        } pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef long int __jmp_buf[8];
enum {
    PTHREAD_CREATE_JOINABLE, PTHREAD_CREATE_DETACHED
};
enum {
    PTHREAD_MUTEX_TIMED_NP,
    PTHREAD_MUTEX_RECURSIVE_NP,
    PTHREAD_MUTEX_ERRORCHECK_NP,
    PTHREAD_MUTEX_ADAPTIVE_NP
};
enum {
    PTHREAD_INHERIT_SCHED, PTHREAD_EXPLICIT_SCHED
};
enum {
    PTHREAD_SCOPE_SYSTEM, PTHREAD_SCOPE_PROCESS
};
enum {
    PTHREAD_PROCESS_PRIVATE, PTHREAD_PROCESS_SHARED
};
struct _pthread_cleanup_buffer {
    void (* __routine)(void *);
    void * __arg;
    int __canceltype;
    struct _pthread_cleanup_buffer * __prev;
};
enum {
    PTHREAD_CANCEL_ENABLE, PTHREAD_CANCEL_DISABLE
};
enum {
    PTHREAD_CANCEL_DEFERRED, PTHREAD_CANCEL_ASYNCHRONOUS
};
extern int pthread_create(pthread_t * __restrict __newthread,
                          const pthread_attr_t * __restrict __attr,
                          void * (* __start_routine)(void *),
                          void * __restrict __arg) __attribute__((__nothrow__,__nonnull__(1, 3)));
extern void pthread_exit(void * __retval) __attribute__((__noreturn__));
extern int pthread_join(pthread_t __th, void * * __thread_return);
extern int pthread_detach(pthread_t __th) __attribute__((__nothrow__));
extern pthread_t pthread_self(void) __attribute__((__nothrow__,const));
extern int pthread_equal(pthread_t __thread1,
                         pthread_t __thread2) __attribute__((__nothrow__));
extern int pthread_attr_init(pthread_attr_t * __attr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_attr_destroy(pthread_attr_t * __attr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_attr_getdetachstate(const pthread_attr_t * __attr,
                                       int * __detachstate) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_setdetachstate(pthread_attr_t * __attr,
                                       int __detachstate) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_attr_getguardsize(const pthread_attr_t * __attr,
                                     size_t * __guardsize) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_setguardsize(pthread_attr_t * __attr,
                                     size_t __guardsize) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_attr_getschedparam(const pthread_attr_t * __restrict __attr,
                                      struct sched_param * __restrict __param) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_setschedparam(pthread_attr_t * __restrict __attr,
                                      const struct sched_param * __restrict __param) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_getschedpolicy(const pthread_attr_t * __restrict __attr,
                                       int * __restrict __policy) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_setschedpolicy(pthread_attr_t * __attr,
                                       int __policy) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_attr_getinheritsched(const pthread_attr_t * __restrict __attr,
                                        int * __restrict __inherit) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_setinheritsched(pthread_attr_t * __attr,
                                        int __inherit) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_attr_getscope(const pthread_attr_t * __restrict __attr,
                                 int * __restrict __scope) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_setscope(pthread_attr_t * __attr,
                                 int __scope) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_attr_getstackaddr(const pthread_attr_t * __restrict __attr,
                                     void * * __restrict __stackaddr) __attribute__((__nothrow__,__nonnull__(1, 2),__deprecated__));
extern int pthread_attr_setstackaddr(pthread_attr_t * __attr,
                                     void * __stackaddr) __attribute__((__nothrow__,__nonnull__(1),__deprecated__));
extern int pthread_attr_getstacksize(const pthread_attr_t * __restrict __attr,
                                     size_t * __restrict __stacksize) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_attr_setstacksize(pthread_attr_t * __attr,
                                     size_t __stacksize) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_setschedparam(pthread_t __target_thread,
                                 int __policy,
                                 const struct sched_param * __param) __attribute__((__nothrow__,__nonnull__(3)));
extern int pthread_getschedparam(pthread_t __target_thread,
                                 int * __restrict __policy,
                                 struct sched_param * __restrict __param) __attribute__((__nothrow__,__nonnull__(2, 3)));
extern int pthread_setschedprio(pthread_t __target_thread,
                                int __prio) __attribute__((__nothrow__));
extern int pthread_once(pthread_once_t * __once_control,
                        void (* __init_routine)(void)) __attribute__((__nonnull__(1, 2)));
extern int pthread_setcancelstate(int __state, int * __oldstate);
extern int pthread_setcanceltype(int __type, int * __oldtype);
extern int pthread_cancel(pthread_t __th);
extern void pthread_testcancel(void);
typedef struct {
            struct {
                __jmp_buf __cancel_jmp_buf; int __mask_was_saved;
            } __cancel_jmp_buf[1];
            void * __pad[4];
        } __pthread_unwind_buf_t __attribute__((__aligned__));
struct __pthread_cleanup_frame {
    void (* __cancel_routine)(void *);
    void * __cancel_arg;
    int __do_it;
    int __cancel_type;
};
extern void __pthread_register_cancel(__pthread_unwind_buf_t * __buf);
extern void __pthread_unregister_cancel(__pthread_unwind_buf_t * __buf);
extern void __pthread_unwind_next(__pthread_unwind_buf_t * __buf) __attribute__((__noreturn__,__weak__));
struct __jmp_buf_tag;
extern int __sigsetjmp(struct __jmp_buf_tag * __env,
                       int __savemask) __attribute__((__nothrow__));
extern int pthread_mutex_init(pthread_mutex_t * __mutex,
                              const pthread_mutexattr_t * __mutexattr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutex_destroy(pthread_mutex_t * __mutex) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutex_trylock(pthread_mutex_t * __mutex) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutex_lock(pthread_mutex_t * __mutex) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutex_unlock(pthread_mutex_t * __mutex) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutex_getprioceiling(const pthread_mutex_t * __restrict __mutex,
                                        int * __restrict __prioceiling) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_mutex_setprioceiling(pthread_mutex_t * __restrict __mutex,
                                        int __prioceiling,
                                        int * __restrict __old_ceiling) __attribute__((__nothrow__,__nonnull__(1, 3)));
extern int pthread_mutexattr_init(pthread_mutexattr_t * __attr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutexattr_destroy(pthread_mutexattr_t * __attr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutexattr_getpshared(const pthread_mutexattr_t * __restrict __attr,
                                        int * __restrict __pshared) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_mutexattr_setpshared(pthread_mutexattr_t * __attr,
                                        int __pshared) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutexattr_getprotocol(const pthread_mutexattr_t * __restrict __attr,
                                         int * __restrict __protocol) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_mutexattr_setprotocol(pthread_mutexattr_t * __attr,
                                         int __protocol) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t * __restrict __attr,
                                            int * __restrict __prioceiling) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_mutexattr_setprioceiling(pthread_mutexattr_t * __attr,
                                            int __prioceiling) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_cond_init(pthread_cond_t * __restrict __cond,
                             const pthread_condattr_t * __restrict __cond_attr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_cond_destroy(pthread_cond_t * __cond) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_cond_signal(pthread_cond_t * __cond) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_cond_broadcast(pthread_cond_t * __cond) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_cond_wait(pthread_cond_t * __restrict __cond,
                             pthread_mutex_t * __restrict __mutex) __attribute__((__nonnull__(1, 2)));
extern int pthread_cond_timedwait(pthread_cond_t * __restrict __cond,
                                  pthread_mutex_t * __restrict __mutex,
                                  const struct timespec * __restrict __abstime) __attribute__((__nonnull__(1, 2, 3)));
extern int pthread_condattr_init(pthread_condattr_t * __attr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_condattr_destroy(pthread_condattr_t * __attr) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_condattr_getpshared(const pthread_condattr_t * __restrict __attr,
                                       int * __restrict __pshared) __attribute__((__nothrow__,__nonnull__(1, 2)));
extern int pthread_condattr_setpshared(pthread_condattr_t * __attr,
                                       int __pshared) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_key_create(pthread_key_t * __key,
                              void (* __destr_function)(void *)) __attribute__((__nothrow__,__nonnull__(1)));
extern int pthread_key_delete(pthread_key_t __key) __attribute__((__nothrow__));
extern void * pthread_getspecific(pthread_key_t __key) __attribute__((__nothrow__));
extern int pthread_setspecific(pthread_key_t __key,
                               const void * __pointer) __attribute__((__nothrow__));
extern int pthread_atfork(void (* __prepare)(void),
                          void (* __parent)(void),
                          void (* __child)(void)) __attribute__((__nothrow__));
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
static void * run_send(void * args)
{
    (void) args;
    send_run(fn_send,
             fn_flash_receive_source,
             fn_flash_collect_source,
             dt_send);
    0 ? (void) 0 : __assert_fail("0",
                                 "app-tc.c",
                                 50,
                                 __PRETTY_FUNCTION__);
    return (void *) 0;
}
static void * run_receive(void * args)
{
    (void) args;
    receive_run(fn_receive, fn_flash_receive_sink);
    0 ? (void) 0 : __assert_fail("0",
                                 "app-tc.c",
                                 58,
                                 __PRETTY_FUNCTION__);
    return (void *) 0;
}
static void * run_collect(void * args)
{
    (void) args;
    collect_run(fn_collect, fn_flash_collect_sink, dt_collect);
    0 ? (void) 0 : __assert_fail("0",
                                 "app-tc.c",
                                 66,
                                 __PRETTY_FUNCTION__);
    return (void *) 0;
}
int main()
{
    pthread_t send_thread;
    pthread_t receive_thread;
    pthread_t collect_thread;
    pthread_create(&send_thread, (void *) 0, run_send, (void *) 0);
    pthread_create(&receive_thread,
                   (void *) 0,
                   run_receive,
                   (void *) 0);
    pthread_create(&collect_thread,
                   (void *) 0,
                   run_collect,
                   (void *) 0);
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    pthread_cond_init(&cond, (void *) 0);
    pthread_mutex_init(&mutex, (void *) 0);
    while (1)
    {
        pthread_cond_wait(&cond, &mutex);
    }
    return 0;
}
typedef struct {
            unsigned char buffer[50];
        } net_message_t;
void * receive_wire(const char * channel);
__attribute__((tc_blocking)) error_t receive_receive(void * handle,
                                                     net_message_t * msg,
                                                     void * * payload,
                                                     uint8_t * len);
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
                                                  "app-tc.c",
                                                  106,
                                                  __PRETTY_FUNCTION__);
        log_to(logw_handle, payload, len);
    }
}
void * logr_wire(const char * file);
__attribute__((tc_blocking)) error_t logr_read(void * handle,
                                               void * buf,
                                               storage_len_t len,
                                               storage_len_t * res_len);
storage_cookie_t logr_currentOffset(void * handle);
error_t logr_seek(void * handle, storage_cookie_t offset);
storage_len_t logr_getSize(void * handle);
void * send_wire(const char * channel);
__attribute__((tc_blocking)) error_t send_send(void * handle,
                                               net_message_t * msg,
                                               uint8_t len);
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
                                              "app-tc.c",
                                              124,
                                              __PRETTY_FUNCTION__);
    len % sizeof(int32_t) == 0 ? (void) 0 : __assert_fail("(len % sizeof(int32_t)) == 0",
                                                          "app-tc.c",
                                                          125,
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
                                              "app-tc.c",
                                              145,
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