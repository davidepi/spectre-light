#include "console.hpp"

#ifdef _TEST_
int Errors_count[5] = {0,0,0,0,0};
#endif

#undef Console

Console::Console()
{
    Console::motd();
}

void Console::motd()
{
    fprintf(stdout,"Spectre version %s\nReleased on %s, compiled on %s\n",
            SPECTRE_VERSION,SPECTRE_RELEASE,__DATE__);
}

void Console::log(const char* m, const char* v)
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

void Console::notice(const char* s)
{
#ifndef _TEST_
    fprintf(stdout,"[NOTICE] %s\n",s);
#else
    Errors_count[NOTICE_INDEX]++;
#endif
}

void Console::warning(const char* s)
{
#ifndef _TEST_
    fprintf(stderr,"[WARNING] %s\n",s);
#else
    Errors_count[WARNING_INDEX]++;
#endif
}

void Console::severe(const char* s)
{
#ifndef _TEST_
    fprintf(stderr,"[ERROR] %s\n",s);
#else
    Errors_count[ERROR_INDEX]++;
#endif
}

void Console::critical(const char* s)
{
#ifndef _TEST_
    fprintf(stderr,"[CRITICAL] %s\n",s);
    exit(EXIT_FAILURE);
#else
    Errors_count[CRITICAL_INDEX]++;
#endif
}

void Console::log(bool b, const char* m, const char* v)
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

void Console::notice(bool b, const char* s)
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

void Console::warning(bool b, const char* s)
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

void Console::severe(bool b, const char* s)
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

void Console::critical(bool b, const char* s)
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
