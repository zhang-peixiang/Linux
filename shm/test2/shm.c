#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

#define KEY 0x99999999

int main()
{
    int shmid=shmget(KEY,1024,IPC_CREAT|0);
    if(shmid<0)
    {
        perror("shmget");
        return -1;
    }
   
   // void* lp=shmat(shmid,NULL,0);
   // sleep(1);
    
   // shmdt(lp);

    struct shmid_ds buf1;
    shmctl(shmid,IPC_STAT,&buf1);
    printf("%lu\n",buf1.shm_segsz);

    sleep(15);
    shmctl(shmid,IPC_RMID,NULL);
    while(1)
    {
        sleep(1);
    }

    return 0;
}
