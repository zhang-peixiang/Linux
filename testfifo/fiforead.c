#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd =  open("./fifo",O_RDWR);
    if(fd<0)
    {
        perror("open");
        return -1;
    }
    char buf[1024]={0};
    int ret = read(fd,buf,sizeof(buf)-1);
    if(ret<0)
   {
        perror("read");
        return -1;
    }
    printf("buf--> %s\n",buf);

    while(1)
    {
        sleep(1);
    }
    return 0;
}
