#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// signal可更改信号的处理方式
// kill -9   9号信号不能被更改
void sig(int signo)
{
    printf("process is %d\n",signo);
}
int main()
{
    signal(2,sig);

    signal(20,sig);
    signal(9,sig);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
