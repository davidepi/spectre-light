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

#include <cstring> //strcpy
#include <cstdlib> //malloc free
#include <unistd.h> //access
#include <sys/stat.h> //ISDIR

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
    
    ///Copy constructor
    File(const File& old_obj);
    
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
    bool readable()const;
    
    /** \brief Checks wheter a file or a folder is writable or not
     *
     *  Returns true if the file is writable, false otherwise or if some folder
     *  component the path denies search permissions.
     *
     *  /note Note that if the file does not exists this function returns false.
     *  One should perform the same check on the directory where the file should
     *  be writed
     *
     *  \return true if the file is writable, false otherwise
     */
    bool writable()const;
    
    /** \brief Returns the extension of this file
     *
     *  Return a c string representing the extension of this file.
     *  If the File is a directory or has no extension, an empty
     *  string is returned
     *
     *  \return The extension of the file or an empty string if the
     *  file has no extension
     */
    const char* extension()const;
    
    /** \brief Returns the name of the file or the directory
     *
     *  Since the constructor of this class can accept an absolute path to
     *  a file or directory, this method returns just the name of the file or
     *  directory itself
     *
     *  \return The name of the file itself in the path passed to constructor
     */
    const char* filename()const;
    
    /** \brief Returns whether the provided path is absolute or relativ
     *
     *  Returns true if the path is absolute, false otherwise
     *
     *  \return true if the path is absolute, false otherwise
     */
    bool is_absolute()const;
    
    /** \brief Returns whether the provided file is a folder
     *
     *  Returns true if the provided file is a folder, false otherwise.
     *  Note that this function is not complementar to File::is_file()
     *
     *  \return true if the provided file exists and is a directory
     */
    bool is_folder()const;
    
    /** \brief Returns whether the provided file is a regular file
     *
     *  Returns true if the provided file is a regular file, false otherwise
     *  Symlinks are not considered as regular files, so this function is not
     *  complementar to File::is_folder()
     *
     *  \return true if the provided file exists and is a regular file
     */
    bool is_file()const;
    
    ///The path separator for the current OS
    static const char PATH_SEPARATOR;
    ///The current directory where the code is being executed
    static const char* CURRENT_DIR;
    ///The lenghtof the current folder absolute path name. For realpath buffer
    static const size_t CURRENT_DIR_LEN;
    
private:
    
    char* absolute;
    const char* relative;
    const char* ext;
    const char* file;
    //if the stat() called by the constructor succeded
    bool statres;
    //information about the fullpath
    struct stat fileinfo;
};


#endif

