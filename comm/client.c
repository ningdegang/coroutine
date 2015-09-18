#include <ucontext.h>  
#include <stdio.h>  
#include "context.h"
#include "echo.pb.serviceimpl.h"
#include "tcp_rpc_channel.h"
#include "echo.pb.h"
#include "log.h"
  
/*
ucontext_t child_uthread,main_uthread;  
char stack[1024*128];  
void func1(void * arg)  
{  
    puts("child1");  
    swapcontext(&child_uthread,&main_uthread);//切换到child上下文，保存当前上下文到main_uthread  
    puts("child2");  
    swapcontext(&child_uthread,&main_uthread);//切换到child上下文，保存当前上下文到main_uthread  
    puts("child3");  
    swapcontext(&child_uthread,&main_uthread);//切换到child上下文，保存当前上下文到main_uthread  
    puts("child4");  
  
}  
void context_test()  
{  
  
    getcontext(&child_uthread); //获取当前上下文  
    child_uthread.uc_stack.ss_sp = stack;//指定栈空间  
    child_uthread.uc_stack.ss_size = sizeof(stack);//指定栈空间大小  
    child_uthread.uc_stack.ss_flags = 0;  
    child_uthread.uc_link = &main_uthread;//设置后继上下文  
  
    makecontext(&child_uthread,(void (*)(void))func1,0);//修改上下文指向func1函数  
  
    puts("main_uthread0");//如果设置了后继上下文，func1函数指向完后会返回此处  
    swapcontext(&main_uthread,&child_uthread);//切换到child上下文，保存当前上下文到main_uthread  
    puts("asdfasdfasdfasdfasdf");
    swapcontext(&main_uthread,&main_uthread);//切换到child上下文，保存当前上下文到main_uthread  
    puts("asdfasdfasfdasdfasdfasdfasdfasdfasdfasdf");
    puts("main_uthread1");//如果设置了后继上下文，func1函数指向完后会返回此处  
    swapcontext(&main_uthread,&child_uthread);//切换到child上下文，保存当前上下文到main_uthread  
    puts("main_uthread2");//如果设置了后继上下文，func1函数指向完后会返回此处  
    swapcontext(&main_uthread,&child_uthread);//切换到child上下文，保存当前上下文到main_uthread  
    puts("main_uthread3");//如果设置了后继上下文，func1函数指向完后会返回此处  
}  
*/  
static void* work(void* args)
{
    comm::TcpRpcChannel channel("127.0.0.1",  8001);
    EchoReq req;
    EchoRsp rsp;
    req.set_msg("hello");
    MyService_Stub stub(&channel);
    stub.Echo(NULL, &req, &rsp, NULL);
    printf("%s \n", rsp.msg().c_str());
}
int main()  
{  
    //context_test();  
    //MyServiceImpl* service = new MyServiceImpl();
    //register_service(service);
    //run();
    log_init("./clientlog/", 60, 0);
    create_timer(work, 10, false);
    run(8002);
    return 0;  
}  
