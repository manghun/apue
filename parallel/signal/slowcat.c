#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


#define CPS     10
#define BUFSIZE CPS 

static volatile int loop = 0;

static void alrm_handler(int s)
{
    //alarm(1);
    loop = 1;
}

int main(int argc,char **argv)
{
    int sfd;
    int dfd = 1;
    int len,ret,pos;

    char buf[BUFSIZE];
    struct itimerval itv;




    if(argc < 2)
    {
        fprintf(stderr,"Usage....\n");
    }



    sfd = open(argv[1],O_RDONLY);
    
    if(sfd < 0)
    {
        perror("open()");
        exit(1);
    }

    signal(SIGALRM,alrm_handler);
   // alarm(1);
    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;

    if(setitimer(ITIMER_REAL,&itv,NULL) < 0)
    {
        perror("setitimer()");
        exit(1);
    }



    while(1)
    {

        while(!loop)
            pause();
        
        loop = 0;

        len = read(sfd,buf,BUFSIZE);
        if(len < 0)
        {
            perror("read()");
            break;
        }
        if(len == 0)
        {
            break;     
        }

        pos = 0;

        while(len > 0)
        {
            ret = write(dfd,buf+pos,len);
            if(ret < 0)
            {
                perror("write()");
                exit(1);
            }

            
            pos += ret;
            len -= ret;

        }
    }

    close(dfd);
    close(sfd);

    exit(0);
}

