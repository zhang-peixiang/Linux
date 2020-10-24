#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main()
{
    // raise,kill 都可以给任意进程发送信号  raise是封装的kill函数
    printf("process start\n");
   // raise(2);
   // printf("111111");
   // while(1)
   // {
      //  sleep(1);
   // }

    kill(getpid(),9);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
