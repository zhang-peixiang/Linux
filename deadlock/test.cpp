#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#define THREAD_COUNT 2

pthread_mutex_t tex1;
pthread_mutex_t tex2;

void* ThreadStart1(void* arg)
{
    pthread_detach(pthread_self());
    pthread_mutex_lock(&tex1);
    sleep(10);
    pthread_mutex_lock(&tex2);
}


void* ThreadStart2(void* arg)
{
    pthread_detach(pthread_self());
    pthread_mutex_lock(&tex2);
    sleep(10);
    pthread_mutex_lock(&tex1);
}

int main()
{
    pthread_mutex_init(&tex1,NULL);
    pthread_mutex_init(&tex2,NULL);

    pthread_t tid;

    int ret = pthread_create(&tid,NULL,ThreadStart1,NULL);
    if(ret<0)
    {
        perror("pthread_create");
        return -1;
    }
    ret = pthread_create(&tid, NULL,ThreadStart2, NULL);
    if(ret<0)
    {
        perror("pthread_create");
        return -1;
    }

    while(1)
    {
        sleep(10);
    }
    pthread_mutex_destroy(&tex1);
    pthread_mutex_destroy(&tex2);
    return 0;
}
