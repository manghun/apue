#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    
    FILE *fp;
    char *linebuf;
    size_t linesize = 0;
    fp = fopen(argv[1],"r");

    while(1){
        if(getline(&linebuf,&linesize,fp) < 0)
            break;
        else
            printf("%s",linebuf);
    }

    fclose(fp);
    exit(0);
    
}
