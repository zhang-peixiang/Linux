#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    mkfifo("./fifo",0664);

    int fd=open("./fifo",O_RDWR);

    if(fd<0)
    {
        perror("open");
        return -1;
    }

    write(fd,"hello world",11);
    printf("write done.\n");
    while(1)
    {
        sleep(1);
    }
    
    close(fd);
    return 0;
}
