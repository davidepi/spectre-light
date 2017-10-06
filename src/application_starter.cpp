#if defined(WIN32) || defined(WIN64)
#include <process.h>
#define execl _execl
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include "localization.h"

int main(int argc, char* argv[])
{
    //Since i cannot know the full path of the executable, I only append -full
    //or -rgb to argv[0]
    const unsigned char BUF_SIZE = 0xFF;
    char cmd[BUF_SIZE];
    strncpy(cmd,argv[0],BUF_SIZE);
    char* input;
    if(argc<2)
    {
        //no args, request input file
        //can't do this in main.cpp because to call either rgb or full
        //spectrum renderer the input file is needed
#define BUFFER_SIZE 256
        input = (char*)malloc(BUFFER_SIZE*sizeof(char));
        fprintf(stdout,MESSAGE_INPUT_FILE "\n");
        input = fgets(input,BUFFER_SIZE,stdin);
        while(isspace(input[0])) //remove leading space if any. input will
            input++;    //broke but who cares, the image of the program will
                        //be replaced
        int len = (int)(strlen(input)-1); //position of the \n
        //isprint is used to remove some magic characters generated with
        //drag-drop in osx
        while(isspace(input[len]) || !isprint(input[len]))
            input[len--] = '\0';
        if(input[0]=='q')
        {
            fprintf(stdout,MESSAGE_BYE "\n");
            return 0;
        }
    }
    else
        input = argv[1];
    //parse first line
   FILE* fin = fopen(input,"r");
    char buf[11];
    if(fin!=NULL)
    {
        fgets(buf, 11, fin);
        if(strcmp(buf,"#RGB\n")==0) //requested rgb rendering
        {
            strncat(cmd,"-rgb",BUF_SIZE);
            execl(cmd,"spectre-rgb",input,NULL);
        }
        else //defaulting to full spectral rendering
        {
            execl(cmd,"spectre-full",input,NULL);
        }
    }
    else //can't read input, spectre-full will handle the error
    {
        strncat(cmd,"-full",BUF_SIZE);
        execl(cmd,"spectre-full",input,NULL);
    }
}
