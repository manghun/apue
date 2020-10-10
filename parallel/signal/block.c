#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void int_handler(int s)
{
    write(1,"!",1);
}

int main()
{

    
    int i,j;
    sigset_t set;

    signal(SIGINT,int_handler);
    sigemptyset(&set);
    sigaddset(&set,SIGINT);


    for(j = 0;j < 1000;j++)
    {

        sigprocmask(SIG_BLOCK,&set,NULL);
    for(i = 0; i < 5; i++)
    {
        write(1,"*",1);
        sleep(1);
    }
        write(1,"\n",1);
        sigprocmask(SIG_UNBLOCK,&set,NULL);
    }



    exit(0);
}

