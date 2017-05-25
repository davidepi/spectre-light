//Created,  22 Mar 2017
//Last Edit 22 May 2017

/**
 *  \file console.hpp
 *  \brief Console logging
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  22 May 2017
 *  \copyright GNU GPLv3
 */

#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#include <cstdio> //fprintf
#include <cstdlib> //exit

///Version of the software
#define SPECTRE_VERSION "PRE"

///Release date of this version
#define SPECTRE_RELEASE "N.A."

/**
 * \class Console Console.hpp "utility/console.hpp"
 * \brief Console logging
 *
 *  This class is used to print messages to the console. It is a singleton, and
 *  while usually not a good practice I find it handy to print in this way.
 *
 *  A define grant access to an singleton just by writing "Console"
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

private:
    
    //constructor
    Console();
    
    //the first message printed to the console
    void motd();
};

///Access the console just by writing "Console" instead of calling getInstance()
#define Console Console::getInstance()

#endif