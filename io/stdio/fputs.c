#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("test1","w+");
    fputs("ab",fp);
    fclose(fp);
    return 0;
}

