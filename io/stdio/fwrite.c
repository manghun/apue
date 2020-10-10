#include <stdio.h>

int main()
{
    FILE *fp;
       char str[] = "This is runoob.com";
        printf("%ld\n",sizeof(str));
          fp = fopen( "file.txt" , "w"  );
             fwrite(str, sizeof(str) , 1, fp );
              
                fclose(fp);
                  
                   return(0);
}

