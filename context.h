#include <ucontext.h>
#define UTHREAD_MAX_NUM  256 
#define STACK_SIZE 4096
typedef int uthread_t;
enum
{
    idle = 0,
    used,
    suspend
};

struct uthread_struct
{
    int status;
    int parent;
    ucontext_t context;
    char stack[STACK_SIZE];
    void* (*func)(void *arg);
    void *arg;
    void *exit_status;
};


int get_upid();
void panic(void);
void *func(void* a);
void *uthread_func(void* argc);
void main_uthread(void);
void uthread_context_init(int tid);
void uthread_init(void);
void uthread_exit(void *exit_status);
void uthread_helper(void);
int uthread_create(uthread_t *thread, void* (*start_routine)(void*), void *arg);
void uthread_yeild(void);
void uthread_loop(void);
