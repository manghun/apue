#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

int main()
{
    int pd[2];
    int len;
    pid_t pid;
    char buf[BUFSIZE];

    if (pipe(pd) < 0)
    {
        perror("pipe()");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (pid == 0)
    {   
        close(pd[1]);   //关闭写端
        dup2(pd[0],0);
        close(pd[0]);
        execl("/usr/bin/mpg123","mpg123","-",NULL);
    }
    else
    {
        close(pd[0]);
        write(pd[1],"Hello!",6);
        close(pd[1]);
        exit(0);
    }

}