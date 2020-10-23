#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 0x99999999

int main()
{
    int shmid=shmget(KEY,1024,IPC_CREAT | 0664);
    int count=1;
    if(shmid<0)
    {
        perror("shmget");
        return -1;
    }
    void* lp =  shmat(shmid,NULL,0);
    while(count<1000)
    {
        char buf[1024]={0};
        sprintf(buf,"%s--%d\n","hello world",count);
        strncpy((char*)lp,buf,sizeof(buf)-1);
        count++;
        sleep(1);
    }

    return 0;
}
