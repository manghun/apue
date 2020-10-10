#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include "mytbf.h"


#define CPS     10
#define BUFSIZE 1024
#define BURST   100



int main(int argc,char **argv)
{
    int sfd;
    int dfd = 1;
    int len,ret,pos;
    mytbf_t *tbf;
    int size;

    char buf[BUFSIZE];

    if(argc < 2)
    {
        fprintf(stderr,"Usage....\n");
    }

    tbf = mytbf_init(CPS,BURST);

    if(tbf == NULL)
    {
        fprintf(stderr,"mytbf_init() failed!\n");
        exit(1);
    }

    sfd = open(argv[1],O_RDONLY);
    
    if(sfd < 0)
    {
        perror("open()");
        exit(1);
    }

    
    while(1)
    {

        size = mytbf_fetchtoken(tbf,BUFSIZE);


        while((len = read(sfd,buf,size)) < 0)
        {
            if(errno == EINTR)
                continue;
            perror("read()");
            break;
        }
        if(len == 0)
        {
            break;     
        }

        if(size - len > 0)
            mytbf_returntoken(tbf,size-len);

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

    close(sfd);
    mytbf_destroy(tbf);

    exit(0);
}

