#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int g_bowl=0; // 0表示每面  1表示有面

pthread_mutex_t g_tex;// 互斥锁
pthread_cond_t cond; // 变量1--消费
pthread_cond_t productor;// 变量2 --生产

void* EatNoddle(void* arg)
{
    pthread_detach(pthread_self());
    (void)arg;
    while(1)
    {
        pthread_mutex_lock(&g_tex);
        while(g_bowl<=0)
        {
            //调用等待接口， 进入PCB等待队列
            pthread_cond_wait(&cond,&g_tex);
        }
        g_bowl--;
        printf("Eat---g_bowl:%d\n",g_bowl);
        pthread_mutex_unlock(&g_tex);
        // 调用唤醒接口，唤醒PCB等待队列中的线程
        pthread_cond_signal(&productor);
    }
    return NULL;
}

void* MakeNoddle(void* arg)
{
    pthread_detach(pthread_self());
    (void)arg;
    while(1)
    {
        pthread_mutex_lock(&g_tex);
        while(g_bowl>0)
        {
            // 等待
            pthread_cond_wait(&productor,&g_tex);
        }
        
        g_bowl++;
        printf("Make---g_bowl:%d\n",g_bowl);
        pthread_mutex_unlock(&g_tex);
        // 唤醒
        pthread_cond_signal(&cond);
    }
}

int main()
{
    // 初始化
    pthread_mutex_init(&g_tex,NULL);
    pthread_cond_init(&cond,NULL);
    
    pthread_t tid;
    for(int i=0;i<2;i++)
    {
         int ret=pthread_create(&tid,NULL,EatNoddle,NULL);
         if(ret<0)
         {
            perror("pthread_create");
            return -1;
         }
         ret = pthread_create(&tid,NULL,MakeNoddle,NULL);
         if(ret<0)
         {
             perror("pthread_creat");
             return -1;
         }
    }
    while(1)
    {
        sleep(1);
    }

    pthread_mutex_destroy(&g_tex);
    pthread_cond_destroy(&cond);
    return 0;
}
