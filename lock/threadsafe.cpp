#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// 黄牛抢票
// 不加锁会出现几个人抢到了一张票的情况
#define THREAD_COUNT 4  // 4个线程

int g_tickets=100;// 100张票

pthread_mutex_t tex;

struct ThreadData
{
    int num_;
    ThreadData()
    {
        num_=-1;
    }
};


void* ThreadStart(void* arg)
{
    pthread_detach(pthread_self());

    ThreadData* td=(ThreadData*)arg;
    while(1)
    {
        pthread_mutex_lock(&tex); //上锁
        if(g_tickets > 0)
        {
            printf("i am %p-%d,i have ticket is %d\n",pthread_self(),td->num_,g_tickets);
            g_tickets--;
        }
        else
        {
            pthread_mutex_unlock(&tex);
            break;
        }

        pthread_mutex_unlock(&tex);
    }
    delete td;
}

int main()
{
    pthread_mutex_init(&tex,NULL);
    pthread_t tid[THREAD_COUNT];
    for(int i=0;i<THREAD_COUNT;++i)
    {
       struct ThreadData* td=new ThreadData;
       td->num_=i;
       int ret=pthread_create(&tid[i],NULL,ThreadStart,(void*)td);
       if(ret<0)
       {
           perror("pthread_create");
           return -1;
       }

    }
    while(1)
    {
        sleep(1);
    }
    pthread_mutex_destroy(&tex);
    return 0;
}
