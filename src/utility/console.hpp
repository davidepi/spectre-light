//Created,  22 Mar 2017
//Last Edit 26 Nov 2017

/**
 *  \file console.hpp
 *  \brief Console logging
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  26 Nov 2017
 *  \copyright GNU GPLv3
 */


#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#include "localization.h"
#include <cstdio> //fprintf
#include <cstdlib> //exit
#include <string> //std::wstring, std::string
#include <iostream> //std::wcout, std::cout

///Version of the software
#define SPECTRE_VERSION "0.1.0"

///Release date of this version
#define SPECTRE_RELEASE "Dec  3 2017"

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
    static Console& getInstance()
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
     *  logged.
     *
     *  \note The newline character is not needed
     *
     *  \sa log(bool condition, const char* message, const char* verbose)
     *  \sa notice  (const char* message)
     *  \sa warning (const char* message)
     *  \sa severe  (const char* message)
     *  \sa critical(const char* message)
     */
    void log(const char* message, const char* verbose);
    
    /** \brief Log a message
     *
     *  Log a message in the console with a severity of "Notice"
     *
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa notice(bool condition, const char* message)
     *  \sa log (const char* message, const char* verbose)
     *  \sa warning (const char* message)
     *  \sa severe  (const char* message)
     *  \sa critical(const char* message)
     */
    void notice(const char* message);
    
    /** \brief Log a message
     *
     *  Log a message in the console with a severity of "Warning"
     *
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa warning(bool condition, const char* message)
     *  \sa log (const char* message, const char* verbose)
     *  \sa notice (const char* message)
     *  \sa severe  (const char* message)
     *  \sa critical(const char* message)
     */
    void warning(const char* message);
    
    /** \brief Log a message
     *
     *  Log a message in the console with a severity of "Error"
     *
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa severe(bool condition, const char* message)
     *  \sa log (const char* message, const char* verbose)
     *  \sa notice (const char* message)
     *  \sa warning  (const char* message)
     *  \sa critical(const char* message)
     */
    void severe(const char* message);
    
    /** \brief Log a message and kill the program
     *
     *  Log a message in the console with a severity of "Critical", then quit
     *  the program with an exit(EXIT_FAILURE)
     *
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa critical(bool condition, const char* message)
     *  \sa log (const char* message, const char* verbose)
     *  \sa notice (const char* message)
     *  \sa warning  (const char* message)
     *  \sa severe(const char* message)
     */
    void critical(const char* message);
    
    /** \brief Log a message, after evaluating a condition
     *
     *  Evaluate a condition, and if it is true, log a message in the console
     *
     *  \param[in] condition The condition to be evaluated
     *  \param[in] message The message to be logged
     *  \param[in] verbose The message to be logged if the program is launched
     *  in verbose mode. If this parameter is NULL the normal message will be
     *  logged.
     *
     *  \note The newline character is not needed
     *
     *  \sa log(const char* message, const char* verbose)
     *  \sa notice  (bool condition, const char* message)
     *  \sa warning (bool condition, const char* message)
     *  \sa severe  (bool condition, const char* message)
     *  \sa critical(bool condition, const char* message)
     */
    void log(bool condition, const char* message, const char* verbose);
    
    /** \brief Log a message, after evaluating a condition
     *
     *  Evaluate a condition, and if it is true, log a message in the console
     *  with a severity of "Notice"
     *
     *  \param[in] condition The condition to be evaluated
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa notice(const char* message)
     *  \sa log (bool condition, const char* message, const char* verbose)
     *  \sa warning (bool condition, const char* message)
     *  \sa severe  (bool condition, const char* message)
     *  \sa critical(bool condition, const char* message)
     */
    void notice(bool condition, const char* message);
    
    /** \brief Log a message, after evaluating a condition
     *
     *  Evaluate a condition, and if it is true, log a message in the console
     *  with a severity of "Warning"
     *
     *  \param[in] condition The condition to be evaluated
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa warning(const char* message)
     *  \sa log (bool condition, const char* message, const char* verbose)
     *  \sa notice (bool condition, const char* message)
     *  \sa severe  (bool condition, const char* message)
     *  \sa critical(bool condition, const char* message)
     */
    void warning (bool condition, const char* message);
    
    /** \brief Log a message, after evaluating a condition
     *
     *  Evaluate a condition, and if it is true, log a message in the console
     *  with a severity of "Error"
     *
     *  \param[in] condition The condition to be evaluated
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa severe(const char* message)
     *  \sa log (bool condition, const char* message, const char* verbose)
     *  \sa notice (bool condition, const char* message)
     *  \sa warning  (bool condition, const char* message)
     *  \sa critical(bool condition, const char* message)
     */
    void severe  (bool condition, const char* message);
    
    /** \brief Log a message, after evaluating a condition, then kill the 
     *  program
     *
     *  Evaluate a condition, and if it is true, log a message in the console
     *  with a severity of "Critical". If the condition is true, this function
     *  quits the program with an exit(EXIT_FAILURE)
     *
     *  \param[in] condition The condition to be evaluated
     *  \param[in] message The message to be logged
     *
     *  \note The newline character is not needed
     *
     *  \sa critical(const char* message)
     *  \sa log (bool condition, const char* message, const char* verbose)
     *  \sa notice (bool condition, const char* message)
     *  \sa warning  (bool condition, const char* message)
     *  \sa severe(bool condition, const char* message)
     */
    void critical(bool condition, const char* message);

    /** \brief Print a progress bar
     *
     * \param[in] done A float in the range [0.0,1.0] representing the completed
     * amount
     * \param[in] eta The estimated remainint time in seconds
     * \sa progressBarDone()
     */
    void progressBar(float done, float eta)const;

    ///Print a completed progress bar
    void progressBarDone()const;

private:
    
    //constructor
    Console();
    
    //the first message printed to the console
    void motd();
};

///Access the console just by writing "Console" instead of calling getInstance()
#define Console Console::getInstance()

#ifdef TESTS
#define LOG_INDEX 0
#define NOTICE_INDEX 1
#define WARNING_INDEX 2
#define ERROR_INDEX 3
#define CRITICAL_INDEX 4
extern int errors_count[5];
#endif

#endif
