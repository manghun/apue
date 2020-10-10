#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FNAME "/tmp/out"

int main(int argc,char **argv[])
{
    int fd;


    fd = open(FNAME,O_WRONLY|O_CREAT|O_TRUNC,0600);

    if(fd < 0)
    {
        perror("open()");
        exit(1);
    }

    //close(1);
    //dup(fd);
    dup2(fd,1);
    
    puts("Hello!");

    close(fd);

    exit(0);
}

