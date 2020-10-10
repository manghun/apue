#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    printf("[%d]:Begin!\n",getpid());

    pid = fork();

    if(pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if(pid == 0)
    {
        printf("[%d]:Child is working!\n",getpid());
    }

    else
    {
        sleep(1);
        printf("[%d]:Parent is working!\n",getpid());
    }

    printf("[%d]:End!\n",getpid());
    
    getchar();
    exit(0);
}

