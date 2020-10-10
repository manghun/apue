#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile int loop = 1;

static void alrm_handler(int s)
{
    loop = 0;

}

int main()
{

    signal(SIGALRM,alrm_handler);
    alarm(5);
    int64_t count = 0;

    while(loop)
        count++;

    printf("%lld\n",count);

    exit(0);
}

