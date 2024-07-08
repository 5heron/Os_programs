#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
sem_t mutex, empty,full;
int buffer[5],get=0,item=0,gitem,put=0,pro[20],con[20];
void *producer(void *arg)
{
    do
    {
        //wait till buffer slot is empty
        sem_wait(&empty);
        //wait to acquire mutex(semaphore) lock
        sem_wait(&mutex);
        buffer[put%5]=item;
        //arg is a pointer which has int value (necessary type conversion is required)
        printf("Producer %d : produced item %d in buffer, buffer[%d] = %d\n",(*(int *)arg),buffer[put%5],put%5,item);
        item++;
        put++;
        //release the mutex(semaphore) lock
        sem_post(&mutex);
        //release the full buffer
        sem_post(&full);
        sleep(3);
    }
    while(put<5);
}
void *consumer(void *arg)
{
    do
    {
        //wait till buffer slot is full
        sem_wait(&full);
        //wait to acquire mutex(semaphore) lock
        sem_wait(&mutex);
        gitem=buffer[get%5];
        //arg is a pointer which has int value (necessary type conversion is required)
        printf("Consumer %d : consumed item %d in buffer, buffer[%d] : %d\n",(*(int *)arg),gitem,get%5,gitem);
        get++;
        //release the mutex(semaphore) lock
        sem_post(&mutex);
        //release the empty buffer
        sem_post(&empty);
        sleep(2);
    }
    while(get<5);
}
void main()
{
    int p,c,j,k;
    pthread_t a[10],b[10];
    //syntax : sem_init(&semaphore_name, processes_shared, value) [Initialises semaphore] 
    sem_init(&mutex,0,1);
    sem_init(&full,0,0);
    sem_init(&empty,0,5);
    printf("\nEnter number of producers : ");
    scanf("%d",&p);
    printf("\nEnter number of consumers : ");
    scanf("%d",&c);
    //syntax : pthread_create(thread_id, thread_attributes, routine, routine_arguement) [Create Thread]
    for(j=0; j<p; j++)
    {
        pro[j]=j;
        pthread_create(&a[j],NULL,producer,&pro[j]);
    }
    for(k=0; k<c; k++)
    {
        con[k]=k;
        pthread_create(&b[k],NULL,consumer,&con[k]);
    }
    //syntax : pthread_join(thread_id, exit_value_ptr) [Suspend main_thread till pthread suspends]
    for(j=0; j<p; j++)
        pthread_join(a[j],NULL);
    for(k=0; k<c; k++)
        pthread_join(b[k],NULL);
}