#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t end;

    end = time(NULL)+5;

    int64_t count = 0;

    while(time(NULL) <= end)
        count++;

    printf("%lld\n",count);






    exit(0);
}

