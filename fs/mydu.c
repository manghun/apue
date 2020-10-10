#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>


#define PATHSIZE 1024

static int64_t mydu(const char *path)
{
    struct stat statres;
    char nextpath[PATHSIZE]; 
    glob_t globres;
    int64_t sum;

    if(lstat(path,&statres) < 0)
    {
        perror("lsata()");
        exit(1);
    }

    if(!S_ISDIR(statres.st_mode))
        return statres.st_blocks/2;

    strncpy(nextpath,path,PATHSIZE);
    strncat(nextpath,"/*",PATHSIZE);
    glob(nextpath,0,NULL,&globres);

    
    strncpy(nextpath,path,PATHSIZE);
    strncat(nextpath,"/.*",PATHSIZE);
    glob(nextpath,GLOB_APPEND,NULL,&globres);

    sum = 0;

    for(int i = 0;i < globres.gl_pathc;i++)
    {
        if(path_noloop(globres.gl_pathv[i]))
        {
            
            sum += mydu(globres.gl_pathv[i]);
        
        }
    }
    sum += statres.st_blocks;
    return sum/2;
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr,"Usage...\n");
        exit(1);
    }

    printf("%lld\n",mydu(argv[1]));
    
    return 0;
}

