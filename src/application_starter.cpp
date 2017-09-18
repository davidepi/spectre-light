#if defined(WIN32) || defined(WIN64)
#include <process.h>
#define execl _execl
#else
#include <unistd.h>
#endif
#include <cstdio>
#include <cstring>

int main(int argc, char* argv[])
{
    //Since i cannot know the full path of the executable, I only append -full
    //or -rgb to argv[0]
    unsigned char BUF_SIZE = 0xFF;
    char cmd[BUF_SIZE];
    strncpy(cmd,argv[0],BUF_SIZE);
    
    if(argc<2)
    {
        //no args, call spectre-full that will handle the error
        strncat(cmd,"-full",BUF_SIZE);
        execl(cmd,"spectre-full",0);
    }
    else
    {
        //parse first line
        FILE* fin = fopen(argv[1],"r");
        char buf[11];
        if(fin!=NULL)
        {
            fgets(buf, 11, fin);
            if(strcmp(buf,"#RGB\n")==0) //requested rgb rendering
            {
                strncat(cmd,"-rgb",BUF_SIZE);
                execl(cmd,"spectre-rgb",argv[1],0);
            }
            else //defaulting to full spectral rendering
            {
                execl(cmd,"spectre-full",argv[1],0);
            }
        }
        else //can't read input, spectre-full will handle the error
        {
            strncat(cmd,"-full",BUF_SIZE);
            execl(cmd,"spectre-full",argv[1],0);
        }
    }
}
