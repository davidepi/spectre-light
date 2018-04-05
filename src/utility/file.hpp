//Created,   4 Apr 2018
//Last Edit  5 Apr 2018

/**
 *  \file file.hpp
 *  \brief Utilities involving the filesystem
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  5 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <cstring>
#include <unistd.h>

/**
 * \class File file.hpp "utility/file.hpp"
 * \brief Performs operations over a file or directory
 *
 */
class File
{
public:
    
    /** \brief default Constructor
     *
     *  \param[in] path An absolute or relative path to a File or a directory,
     *  existent or non-existent
     */
    File(const char* path);
    
    ///Default destructor
    ~File();
    
    /** \brief Checks whether a file or a folder exists or not
     *
     *  Returns true if the file exists, false otherwise or if some folder of
     *  component the path denies search permissions
     *
     *  \return true if the file exists, false otherwise
     */
    bool exists()const;
    
    /** \brief Checks wheter a file or a folder is readable or not
     *
     *  Returns true if the file is readable, false otherwise or if some folder
     *  component the path denies search permissions
     *
     *  \return true if the file is readable, false otherwise
     */
    bool can_read()const;
    
    /** \brief Checks wheter a file or a folder is writable or not
     *
     *  Returns true if the file is writable, false otherwise or if some folder
     *  component the path denies search permissions
     *
     *  \return true if the file is writable, false otherwise
     */
    bool can_write()const;
    
private:
    
    char* filename;
    const char* extension;
};


#endif

