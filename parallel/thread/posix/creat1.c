#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


static void * func(void *)
{
    puts("Thread is working!\n");

    return NULL;
} 

int main()
{

    pthread_t tid;

    puts("Begin!\n");

    pthread_create(&tid,NULL,func,NULL);

    printf("End!\n");
    return 0;
}

