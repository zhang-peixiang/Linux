#include <stdio.h>
#include <signal.h>
#include <unistd.h>

struct sigaction oldact;

void sigcb(int signo)
{
    printf("signo is %d\n",signo);
}

// 用sigaction函数来改变信号的默认实现方式
// sigaction 是改变了sigaction这个结构体
// signal是改变了sa_handler的函数
int main()
{
    struct sigaction newact;
    newact.sa_handler=sigcb;
    sigemptyset(&newact.sa_mask);

    newact.sa_flags=0;

    sigaction(2,&newact,&oldact);
    
    while(1)
    {
        sleep(1);
    }
    return 0;
}
