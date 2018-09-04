//Created,  22 Mar 2017
//Last Edit 28 Mar 2018

/**
 *  \file console.hpp
 *  \brief Console logging
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  28 Mar 2018
 *  \copyright GNU GPLv3
 */


#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#include "localization.h"
#include <cstdio> //fprintf
#include <cstdlib> //exit
#include <string> //std::wstring, std::string
#include <iostream> //std::wcout, std::cout
#include <cstdarg> //va_start, va_end

#ifdef _WIN32
#include <conio.h> //_getch()
#endif

///Version of the software
#define SPECTRE_VERSION_MAJOR "0.2.0"
#if defined(GIT_COMMIT_HASH) && defined (GIT_COMMIT_NO) && defined(GIT_BRANCH)
#define SPECTRE_VERSION SPECTRE_VERSION_MAJOR  " build " GIT_COMMIT_NO " (" \
        GIT_COMMIT_HASH ")"
#else
#define SPECTRE_VERSION SPECTRE_VERSION_MAJOR
#endif

///Release date of this version
#define SPECTRE_RELEASE "(Unreleased)"

/**
 * \class Console Console.hpp "utility/console.hpp"
 * \brief Console logging
 *
 *  This class is used to print messages to the console. It is a singleton, and
 *  while usually not a good practice I find it handy to print in this way.
 *
 *  A define grant access to this singleton just by writing "Console"
 */
class Console
{
public:

    ///Get an instance of the console
    static Console& instance()
    {
        static Console instance;
        return instance;
    }

    ///Avoid a copy of the object
    Console(Console const&) = delete;

    ///Avoid a copy of the object
    void operator=(Console const&) = delete;

    /** \brief Log a message
     *
     *  Log a message in the console
     *
     *  \param[in] message The message to be logged
     *  \param[in] verbose The message to be logged if the program is launched
     *  in verbose mode. If this parameter is NULL the normal message will be
     *  logged. Format strings are NOT supported
     *
     *  \note The newline character is not needed
     *
     *  \sa notice  (const char* message)
     *  \sa warning (const char* message)
     *  \sa severe  (const char* message)
     *  \sa critical(const char* message)
     */
    void log(const char* message, const char* verbose);

    /** \brief Log a message
     *
     *  Log a message in the console with a severity of "Notice". Format strings
     *  are supported
     *
     *  \param[in] format The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa log (const char* message, const char* verbose)
     *  \sa warning (const char* message, ...)
     *  \sa severe  (const char* message, ...)
     *  \sa critical(const char* message, ...)
     */
    void notice(const char* format, ...);

    /** \brief Log a message
     *
     *  Log a message in the console with a severity of "Warning". Format
     *  strings are supported
     *
     *  \param[in] format The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa log (const char* message, const char* verbose)
     *  \sa notice (const char* message, ...)
     *  \sa severe  (const char* message, ...)
     *  \sa critical(const char* message, ...)
     */
    void warning(const char* format, ...);

    /** \brief Log a message
     *
     *  Log a message in the console with a severity of "Error". Format strings
     *  are supported
     *
     *  \param[in] format The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa log (const char* message, const char* verbose)
     *  \sa notice (const char* message, ...)
     *  \sa warning  (const char* message, ...)
     *  \sa critical(const char* message, ...)
     */
    void severe(const char* format, ...);

    /** \brief Log a message and kill the program
     *
     *  Log a message in the console with a severity of "Critical", then quit
     *  the program with an exit(EXIT_FAILURE). Format strings are supported
     *
     *  \param[in] format The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa log (const char* message, const char* verbose)
     *  \sa notice (const char* message, ...)
     *  \sa warning  (const char* message, ...)
     *  \sa severe(const char* message, ...)
     */
    void critical(const char* format, ...);

    /** \brief Print a progress bar
     *
     * \param[in] done A float in the range [0.0,1.0] representing the completed
     * amount
     * \param[in] eta The estimated remainint time in seconds
     * \sa progressBarDone()
     */
    void progress_bar(float done, float eta) const;

    ///Print a completed progress bar
    void progress_bar_done() const;

private:

    //constructor
    Console();

    //the first message printed to the console
    void motd();
};

///Access the console just by writing "Console" instead of calling instance()
#define Console Console::instance()

#ifdef TESTS
#define LOG_INDEX 0
#define NOTICE_INDEX 1
#define WARNING_INDEX 2
#define ERROR_INDEX 3
#define CRITICAL_INDEX 4
extern int errors_count[5];
#endif

#endif
