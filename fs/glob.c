#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#define PAT "/etc/a*.conf"

#if 0
static int errfun_(char *errpath,int eerrno)
{
    puts(errpath);
    fprintf(stderr,"ERROR MSG:%s\n",strerror(error));
    return 0;
}
#endif

int main()
{
    int err;
    glob_t globres;

    err = glob(PAT,0,NULL,&globres);

    if(err)
    {
        printf("Error code = %d\n",err);
        exit(1);
    }
    
    for(int i = 0; i < globres.gl_pathc; i++)
        puts(globres.gl_pathv[i]);

    globfree(&globres);
    exit(0);
}

