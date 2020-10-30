#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigcb(int signo)
{
    printf("signo is %d\n",signo);
}


// 对此进程发射2号信号和35号信号各5次
// 现象：在信号阻塞时，信号不着急处理。
// 当解除信号阻塞时，打印1次2号信号5次35号信号
// 原因：2号信号是非可靠信号，35号信号是可靠信号
int main()
{
    signal(2,sigcb);
    signal(35,sigcb);
    sigset_t oldset,newset;

    // 将函数初始化信号集合oldset设置为空
    sigemptyset(&oldset);

    // 将信号集合设置为所有信号的集合
    sigfillset(&newset);

    // 设置信号的阻塞
    sigprocmask(SIG_SETMASK,&newset,&oldset);

    getchar();

    // 取消信号的阻塞
    sigprocmask(SIG_SETMASK,&oldset,NULL);

    return 0;
}
