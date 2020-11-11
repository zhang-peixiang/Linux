#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>

#define CAPACITY 5

#define THREAD_COUNT 2

pthread_mutex_t mutex_;

class SafeQueue
{
    public:
    SafeQueue()
    {
        capacity_=CAPACITY;
        pthread_mutex_init(&mutex_,NULL);
        pthread_cond_init(&productor_cond,NULL);
        pthread_cond_init(&consume_cond,NULL);

    }

    ~SafeQueue()
    {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&productor_cond);
        pthread_cond_destroy(&consume_cond);

    }
    
    void Push(int data)
    {
        pthread_mutex_lock(&mutex_);
        while(queue_.size()>=capacity_)
        {
            pthread_cond_wait(&productor_cond,&mutex_);
        }
        queue_.push(data);
        pthread_mutex_unlock(&mutex_);
        pthread_cond_signal(&consume_cond);

    }


    void Pop(int* data)
    {
        pthread_mutex_lock(&mutex_);
        while(queue_.empty())
        {
            pthread_cond_wait(&consume_cond,&mutex_);
        }
        *data=queue_.front();
        queue_.pop();
        pthread_mutex_unlock(&mutex_);
        pthread_cond_signal(&productor_cond);
    }
    private:
        std::queue<int> queue_;

        size_t capacity_;

        pthread_mutex_t mutex_;
        pthread_cond_t productor_cond;
        pthread_cond_t consume_cond; 
};

int count=0;
void* PushStart(void* arg)
{
    SafeQueue* sq=(SafeQueue*)arg;
    while(1)
    {
        pthread_mutex_lock(&mutex_);
        sq->Push(count);
        printf("i am %p,i product %d\n",pthread_self(),count);
        count++;
        pthread_mutex_unlock(&mutex_);
    }
}


void* PopStart (void* arg)
{
    SafeQueue* sq=(SafeQueue*)arg;
    while(1)
    {
        int data;
        sq->Pop(&data); 
        printf("i am %p,i consume %d\n",pthread_self(),data);
    }
}
int main()
{
    pthread_mutex_init(&mutex_,NULL);
    SafeQueue* sq=new SafeQueue();


    pthread_t productor[THREAD_COUNT],consume[THREAD_COUNT];
    for(int i=0;i<THREAD_COUNT;i++)
    {
        int ret = pthread_create(&productor[i], NULL, PushStart,(void*)sq);
        if(ret<0)
        {
            perror("pthread_create");
            return -1;
        }

        ret = pthread_create(&consume[i],NULL,PopStart,(void*)sq);
        if(ret<0)
        {
            perror("pthread_create");
            return -1;
        }
    }

    for(int i=0;i<THREAD_COUNT;i++)     
    {
         pthread_join(consume[i],NULL);
         pthread_join(productor[i],NULL);
    }
    delete sq;
    pthread_mutex_destroy(&mutex_);

    return 0;
}

