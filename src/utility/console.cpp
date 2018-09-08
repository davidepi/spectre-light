//author: Davide Pizzolotto
//license: GNU GPLv3

#include "console.hpp"

#ifdef TESTS
int errors_count[5] = {0, 0, 0, 0, 0};
#ifndef UNUSED
#define UNUSED(x) (void)x;
#endif
#endif

#undef Console

#ifndef SPECTRE_COLOURED_OUTPUT
#define NOTICE "NOTICE"
#define WARNING "WARNING"
#define ERROR "ERROR"
#define CRITICAL "CRITICAL"
#define SPNRM  ""
#define SPRED  ""
#define SPGRN  ""
#define SPYEL  ""
#define SPBLU  ""
#define SPCYN  ""
#else
#define SPNRM  "\x1B[0m"
#define SPRED  "\x1B[31m"
#define SPGRN  "\x1B[32m"
#define SPYEL  "\x1B[33m"
#define SPBLU  "\x1B[34m"
#define SPCYN  "\x1B[36m"
#define NOTICE SPCYN "NOTICE" SPNRM
#define WARNING SPYEL "WARNING" SPNRM
#define ERROR SPRED "ERROR" SPNRM
#define CRITICAL SPRED "CRITICAL" SPNRM
#endif

Console::Console()
{
    Console::motd();
}

void Console::motd()
{
#ifdef _MSC_VER
    //this trick is necessary since _MSC_VER is an integer
    //#_MSC_VER does not seem to work
#define COMPILER_NAME "MS Visual C++"
    char COMPILER_VERSION[6];
    snprintf(COMPILER_VERSION, 6, "%02d.%02d", _MSC_VER/100, _MSC_VER%100);
#endif
#ifndef SUPPRESS_MOTD
    fprintf(stdout, "Spectre version %s\nCompiled with %s version %s on %s\n",
           SPECTRE_VERSION, COMPILER_NAME, COMPILER_VERSION, __DATE__);
#ifdef DEBUG
    fprintf(stdout, MESSAGE_DEBUG "\n");
#endif
#ifdef SPECTRAL
    fprintf(stdout,"Using full-spectrum renderer\n");
#else
    fprintf(stdout, "Using " SPRED "r" SPGRN "g" SPBLU "b" SPNRM " renderer\n");
#endif
#endif
}

void Console::log(const char* m, const char* v)
{
#ifndef TESTS
    if(v == NULL) //TODO or program not launched with verbose flag
        fprintf(stdout,"%s\n",m);
    else
        fprintf(stdout,"%s\n",v);
#else
    UNUSED(m);
    UNUSED(v);
    errors_count[LOG_INDEX]++;
#endif
}

void Console::notice(const char* format, ...)
{
#ifndef TESTS
    fprintf(stdout,"[" NOTICE "] ");
    va_list args;
    va_start(args,format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout,"\n");
#else
    UNUSED(format);
    errors_count[NOTICE_INDEX]++;
#endif
}

void Console::warning(const char* format, ...)
{
#ifndef TESTS
    fprintf(stderr,"[" WARNING "] ");
    va_list args;
    va_start(args,format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr,"\n");
#else
    UNUSED(format);
    errors_count[WARNING_INDEX]++;
#endif
}

void Console::severe(const char* format, ...)
{
#ifndef TESTS
    fprintf(stderr,"[" ERROR "] ");
    va_list args;
    va_start(args,format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr,"\n");
#else
    UNUSED(format);
    errors_count[ERROR_INDEX]++;
#endif
}

void Console::critical(const char* format, ...)
{
#ifndef TESTS
    fprintf(stderr,"[" CRITICAL "] ");
    va_list args;
    va_start(args,format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr,"\n");
    fflush(stderr);
#ifdef _WIN32
    std::cout << "Pres any key to exit" << std::endl;
    _getch(); //avoid automatic closing the window
#endif
    exit(EXIT_FAILURE);
#else
    UNUSED(format);
    errors_count[CRITICAL_INDEX]++;
#endif
}

void Console::progress_bar_done() const
{
#ifdef _WIN32
    std::cout<<"\r(####################) "<<SPGRN<< "100% Done!"<<SPNRM
              <<std::endl;
#else
    std::cout << "\33[2K\r(####################) " << SPGRN << "100% Done!"
              << SPNRM
              << std::endl;
#endif
}

void Console::progress_bar(float done, float eta) const
{
    done *= 20;
    const char fullblock = '#';
    const char emptyblock = '-';
    std::string progress;

    int i = 0;
    while(i<(int)done)
    {
        progress.push_back(fullblock);
        i++;
    }
    while(i<20)
    {
        progress.push_back(emptyblock);
        i++;
    }
#ifdef _WIN32
    std::cout<<"("<<progress<<") "<<(int)(done*5)<<"%\tETA:"<<eta<<" s\r";
#else
    std::cout << "\33[2K\r(" << progress << ") " << (int)(done*5) << "%\tETA:"
              << eta << " s";
#endif
    fflush(stdout);
}
