//Created,   4 Apr 2018
//Last Edit 19 Apr 2018

/**
 *  \file file.hpp
 *  \brief Utilities involving the filesystem
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  19 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <cstring> //strcpy
#include <cstdlib> //malloc free
#include <vector>
#include <string>
// -- *nix only
#include <unistd.h> //access
#include <sys/stat.h> //ISDIR mkdir
#include <dirent.h> //opendir & co
//

/**
 * \class File file.hpp "utility/file.hpp"
 * \brief Performs operations over a file or directory
 *
 *  This class contains a set of tools to handle directories and files. Upon
 *  creation, the relative path to a file, whether existent or not, will be
 *  resolved as absolute path. The relative path will be lost in the process
 *  and only the absolute one is kept.
 *  If the file is actually a directory, it is kept always without the ending
 *  path separator
 *
 *  /note Relative paths are resolved from the working directory when the
 *  application was started. Changing the directory later will result in
 *  incorrectly generated paths
 *
 *  Methods provided by this class are focused on retrieval, listing and
 *  creation of directories
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
    bool exists() const;

    /** \brief Checks wheter a file or a folder is readable or not
     *
     *  Returns true if the file is readable, false otherwise or if some folder
     *  component the path denies search permissions
     *
     *  \return true if the file is readable, false otherwise
     */
    bool readable() const;

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
    bool writable() const;

    /** \brief Returns the extension of this file
     *
     *  Return a c string representing the extension of this file.
     *  If the File is a directory or has no extension, an empty
     *  string is returned
     *
     *  \return The extension of the file or an empty string if the
     *  file has no extension
     */
    const char* extension() const;

    /** \brief Returns the name of the file or the directory
     *
     *  Since the constructor of this class can accept an absolute path to
     *  a file or directory, this method returns just the name of the file or
     *  directory itself
     *
     *  \return The name of the file itself in the path passed to constructor
     */
    const char* filename() const;

    /** \brief Returns the absolute path for this file
     *
     *  Note that if the provided path is / in a *nix system, the filename will
     *  be considered / as well. On the other hand, if the provided path is
     *  /file, the filename will be considered `file`
     *
     *  /return The absolute path for this file or directory
     */
    const char* absolute_path() const;

    /** \brief Returns whether the provided file is a folder
     *
     *  Returns true if the provided file is a folder, false otherwise.
     *  Note that this function is not complementar to File::is_file()
     *
     *  \return true if the provided file exists and is a directory
     */
    bool is_folder() const;

    /** \brief Returns whether the provided file is a regular file
     *
     *  Returns true if the provided file is a regular file, false otherwise
     *  Symlinks are not considered as regular files, so this function is not
     *  complementar to File::is_folder()
     *
     *  \return true if the provided file exists and is a regular file
     */
    bool is_file() const;

    /** \brief Returns the parent folder of this file
     *
     *  Returns the folder containing the file passed at construction time. If
     *  the file passes at construction time was a folder, this method returns
     *  `..` from that file.
     *
     *  \return A File class containing the parent directory of the current file
     */
    File get_parent() const;

    /** \brief Creates the current folder
     *
     *  If the path specified at construction time specifies a non-existing
     *  folder, this method will create it. However, if some elements of the
     *  path are non-existent or non-readable or the parent is non-writable,
     *  nothing will be created and this method will return false
     *
     *  \return true if the creation was successfull, false otherwise
     *  \sa mkdirs()
     */
    bool mkdir();

    /** \brief Creates every missing folder in the path
     *
     *  This method is the recursive version of File::mkdir(). It will attempt
     *  the creation of every missing directory in the path referencing the
     *  element given at construction time, which is interpreted as a folder
     *  and created as well. If some element of the path are non-writable
     *  this method will return false.
     *
     *  \return true if the creation of every element in the path was
     *  successfull, false otherwise
     *  \sa mkdir()
     */
    bool mkdirs();

    /** \brief List directory contents
     *
     *  Returns a vector containing File classes where every class is contained
     *  in the current directory. This method does not list . and ..
     *
     *  \param[out] retval The vector containing the list of file of the current
     *  directory
     */
    void ls(std::vector<File>* retval) const;

    /** \brief Appends a path to the current one
     *
     *  Given a relative path as input, this function append the path to the one
     *  represented by the current class. Note that no checks are performed on
     *  the current class, so be aware that if the current class represents a
     *  file, it will be treated as a folder after calling this method
     *
     *  \param[in] path A relative path that will be appended to the current
     *  class
     */
    File& append(const char* path);

    ///assignment operator
    File& operator=(const File& old);

    ///The path separator for the current OS
    static const char PATH_SEPARATOR;
    ///The path separator for the current OS, string version
    static const char* PATH_SEPARATOR_STRING;

private:

    char* absolute;
    const char* ext;
    const char* file;
    //if the stat() called by the constructor succeded
    bool statres;
    //information about the fullpath
    struct stat fileinfo;
};

///Determine if a path is absolute or not
inline bool is_absolute(const char* path)
{
    return path[0] == File::PATH_SEPARATOR;
}


#endif

