#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    puts("Begin!");
    fflush(NULL);
    execl("/bin/date","date","+%s",NULL);



    puts("End!");
    exit(0);
}

