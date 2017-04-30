#include "utility.hpp"

#ifdef _TEST_
int Errors_count[5] = {0,0,0,0,0};
#endif

void log(const char* m, const char* v)
{
#ifndef _TEST_
    if(v == NULL) //TODO or program not launched with verbose flag
        fprintf(stdout,"%s\n",m);
    else
        fprintf(stdout,"%s\n",v);
#else
    Errors_count[LOG_INDEX]++;
#endif
}

void notice(const char* s)
{
#ifndef _TEST_
    fprintf(stdout,"[NOTICE] %s\n",s);
#else
    Errors_count[NOTICE_INDEX]++;
#endif
}

void warning(const char* s)
{
#ifndef _TEST_
    fprintf(stderr,"[WARNING] %s\n",s);
#else
    Errors_count[WARNING_INDEX]++;
#endif
}

void severe(const char* s)
{
#ifndef _TEST_
    fprintf(stderr,"[ERROR] %s\n",s);
#else
    Errors_count[ERROR_INDEX]++;
#endif
}

void critical(const char* s)
{
#ifndef _TEST_
    fprintf(stderr,"[CRITICAL] %s\n",s);
    exit(EXIT_FAILURE);
#else
    Errors_count[CRITICAL_INDEX]++;
#endif
}

void log(bool b, const char* m, const char* v)
{
    if(b)
    {
#ifndef _TEST_
        if(v == NULL) //TODO or program not launched with verbose flag
            fprintf(stdout,"%s\n",m);
        else
            fprintf(stdout,"%s\n",v);
#else
        Errors_count[LOG_INDEX]++;
#endif
    }
}

void notice(bool b, const char* s)
{
    if(b)
    {
#ifndef _TEST_
        fprintf(stdout,"[NOTICE] %s\n",s);
#else
        Errors_count[NOTICE_INDEX]++;
#endif
    }
}

void warning(bool b, const char* s)
{
    if(b)
    {
#ifndef _TEST_
        fprintf(stderr,"[WARNING] %s\n",s);
#else
        Errors_count[WARNING_INDEX]++;
#endif
    }
}

void severe(bool b, const char* s)
{
    if(b)
    {
#ifndef _TEST_
        fprintf(stderr,"[ERROR] %s\n",s);
#else
        Errors_count[ERROR_INDEX]++;
#endif
    }
}

void critical(bool b, const char* s)
{
    if(b)
    {
#ifndef _TEST_
        fprintf(stderr,"[CRITICAL] %s\n",s);
        exit(EXIT_FAILURE);
#else
        Errors_count[CRITICAL_INDEX]++;
#endif
    }
}
