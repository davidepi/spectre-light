//author: Davide Pizzolotto
//license: GNU GPLv3

#include "file.hpp"

#ifdef _WIN32
const char File::PATH_SEPARATOR = '\\';
const char* File::PATH_SEPARATOR_STRING = "\\";
#else
const char File::PATH_SEPARATOR = '/';
const char* File::PATH_SEPARATOR_STRING = "/";
#endif

//given an absolute path like "/root" and a relative like "../home/User/./"
//resolves the "../" and "./" and removes "//"
static void append_relative(const char* abs, const char* rel, char* out)
{
    strcpy(out, abs);
    int absolute_index = (int)strlen(abs);
    unsigned int relative_index = 0;
    if(rel[0] == '.')
    {
        //resolve ../file
        if(rel[1] == '.' && rel[2] == File::PATH_SEPARATOR)
        {
            relative_index = 2;
            //backtrack to previous / in the absolute path
            //(guaranteed to exists since file is absolute)
            //position right on / ready to be substituted
            while(absolute_index-->0 &&
                  out[absolute_index] != File::PATH_SEPARATOR);
        }
        else if(rel[1] == File::PATH_SEPARATOR) //resolve ./file
            relative_index = 1;
    }
    if(rel[relative_index] != File::PATH_SEPARATOR)
        out[absolute_index++] = File::PATH_SEPARATOR;
    /*
     *  at this point
     *  -> relative path does not start with . (checked in this if)
     *  -> relative starts with / or a filename
     *  -> absolute path ends with / if relative does not starts with /
     */
    while(relative_index<strlen(rel))
    {
        if(rel[relative_index] == File::PATH_SEPARATOR)
        {
            if(rel[relative_index+1] == '.')
            {
                //handle /./
                if(rel[relative_index+2] == File::PATH_SEPARATOR ||
                   rel[relative_index+2] == 0)
                {
                    relative_index += 2;
                    continue;
                }
                    //handle /../
                else if(rel[relative_index+2] == '.' &&
                        (rel[relative_index+3] == File::PATH_SEPARATOR ||
                         rel[relative_index+3] == 0))
                {
                    relative_index += 3;
                    //avoid out of bounds if too many ../../../
                    if(absolute_index<=1)
                        continue;
                    absolute_index -= 2;
                    while((absolute_index--)>0 &&
                          out[absolute_index] != File::PATH_SEPARATOR);
                    continue;
                }
            }
                //handle //
            else if(rel[relative_index+1] == File::PATH_SEPARATOR)
            {
                relative_index++;
                continue;
            }
        }
        out[absolute_index++] = rel[relative_index++];
    }
    //remove last trailing char, if exists and not root trailing
    if(out[absolute_index-1] == File::PATH_SEPARATOR && absolute_index>1)
        absolute_index--;
    out[absolute_index] = 0;
}

File::File(const char* path)
{
    int pathlen = (int)strlen(path);
    if(is_absolute(path)) //absolute. But need to resolve ../
    {
        absolute = (char*)malloc(sizeof(char)*(pathlen+1));
        append_relative("", path, absolute);
    }
    else //resolve the relative path
    {
        char* current_dir;
        int current_dir_len;
#ifdef _WIN32
        current_dir_len = GetFullPathName(".", 0, NULL, NULL);
        current_dir = (char*)malloc(sizeof(char)*current_dir_len);
        GetFullPathName(".", 0, current_dir, NULL);
#else
        current_dir = realpath(".", NULL);
        current_dir_len = (int)strlen(current_dir);
#endif
        absolute = (char*)malloc(sizeof(char)*(current_dir_len+1+pathlen+1));
        append_relative(current_dir, path, absolute);
        free((void*)current_dir);
    }
#ifndef _WIN32
    File::statres = stat(absolute, &(File::fileinfo)) == 0;
#endif
    //guaranteed to exists at least the toplevel /
    File::file = strrchr(absolute, File::PATH_SEPARATOR);
    //not /
    if(*(file+1) != 0)
        File::file++;
    File::ext = strrchr(file, '.');
    //set "" as extension instead of NULL if not found
    if(ext == NULL)
        ext = absolute+strlen(absolute);
    else
        ext += 1;
    //hidden file w/o extension (separate case because on windows does not hold)
    if(ext == file+1)
        ext = absolute+strlen(absolute);
}

File::File(const File& old_obj)
{
    File::absolute = (char*)malloc(sizeof(char)*(strlen(old_obj.absolute)+1));
    strcpy(absolute, old_obj.absolute);
    //recalculate offsets(since I cannot blindly copy pointers of other classes)
    File::ext = File::absolute+(old_obj.ext-old_obj.absolute);
    File::file = File::absolute+(old_obj.file-old_obj.absolute);
#ifndef _WIN32
    File::statres = old_obj.statres;
    File::fileinfo = old_obj.fileinfo;
#endif
}

File::~File()
{
    free(File::absolute);
}

const char* File::extension() const
{
    return File::ext;
}

const char* File::filename() const
{
    return File::file;
}

const char* File::absolute_path() const
{
    return File::absolute;
}

bool File::exists() const
{
#ifdef _WIN32
    return _access(absolute, 0x00) == 0;
#else
    return access(absolute, F_OK) == 0;
#endif
}

bool File::readable() const
{
#ifdef _WIN32
    return _access(absolute, 0x02) == 0;
#else
    return access(absolute, R_OK) == 0;
#endif
}

bool File::writable() const
{
#ifdef _WIN32
    return _access(absolute, 0x04) == 0;
#else
    return access(absolute, W_OK) == 0;
#endif
}

bool File::is_folder() const
{
#ifdef _WIN32
    DWORD attr = GetFileAttributes(absolute);
    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    return statres && S_ISDIR(fileinfo.st_mode);
#endif
}

bool File::is_file() const
{
#ifdef _WIN32
    DWORD attr = GetFileAttributes(absolute);
    return (attr & FILE_ATTRIBUTE_DIRECTORY) == 0;
#else
    return statres && S_ISREG(fileinfo.st_mode);
#endif
}

File& File::operator=(const File& old)
{
    File::absolute = (char*)malloc(sizeof(char)*(strlen(old.absolute)+1));
    strcpy(absolute, old.absolute);
    //recalculate offsets(since I cannot blindly copy pointers of other classes)
    File::ext = File::absolute+(old.ext-old.absolute);
    File::file = File::absolute+(old.file-old.absolute);
#ifndef _WIN32
    File::statres = old.statres;
    File::fileinfo = old.fileinfo;
#endif
    return *this;
}

File& File::append(const char* path)
{
    //an extra byte is needed if the file separator needs to be added
    char* newp = (char*)malloc(sizeof(char)*(strlen(absolute)+strlen(path)+2));
    append_relative(absolute, path, newp);
    free(absolute);
    absolute = newp;
#ifndef _WIN32
    File::statres = stat(absolute, &(File::fileinfo)) == 0;
#endif
    File::file = strrchr(absolute, File::PATH_SEPARATOR);
    if(*(file+1) != 0)
        File::file++;
    File::ext = strrchr(file, '.');
    if(ext == NULL)
        ext = absolute+strlen(absolute);
    else
        ext += 1;
    if(ext == file+1)
        ext = absolute+strlen(absolute);
    return *this;
}

File File::get_parent() const
{
    File retval(*this);
    if(retval.file[0] != '/') //not root
    {
        int i = -1;
        //starts from -1 up to - max_decrement
        int max_decrement = (int)(absolute-file);
        //root folder is the parent
        if(max_decrement == -1)
        {
            retval.absolute[1] = 0;
            retval.file = retval.absolute;
            retval.ext = retval.absolute+1;
        }
            //replace the / right before the filename with 0
        else
        {
            retval.absolute[(retval.file-retval.absolute)-1] = 0;
            //update the extension to be "" -> point to the newly inserted 0
            retval.ext = retval.file-1;
            //go back with the file pointer until the last /
            while(i-->max_decrement && file[i] != File::PATH_SEPARATOR);
            //if not root, point to the filename
            if(i != max_decrement)
                retval.file += i+1;
            //else
            /* do nothing, already catched in the max_decrement==-1 */;
        }
    }
    return retval;
}

bool File::mkdir()
{
#ifdef _WIN32
    return CreateDirectory(absolute, NULL);
#else
    bool retval = ::mkdir(absolute, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
    //refresh info about this folder
    File::statres = stat(absolute, &(File::fileinfo)) == 0;
    return retval;
#endif
}

bool File::mkdirs()
{
    int index = 1;
    bool res = File::mkdir(); //attempt a quick execution
    bool created = false;
    if(!res)
    {
        res = true;
        int len = (unsigned int)strlen(absolute);
        while(index<len)
        {
            //reach separator
            while(index<len && absolute[++index] != File::PATH_SEPARATOR);
            absolute[index] = 0;
#ifdef _WIN32
            if(_access(absolute, 0x00) != 0)
#else
            if(access(absolute, F_OK) != 0) //folder does not exist
#endif
            {
                res = File::mkdir();
                created = true;
            }
            //resume searching
            absolute[index] = File::PATH_SEPARATOR;
            if(!res)
                return false;
        }
    }
    else
        created = true;
    //no need to refresh informations since is done by the mkdir() function
    return created;
}

void File::ls(std::vector<File>* retval) const
{
    unsigned int len = (unsigned int)strlen(absolute);
    unsigned int allocated = len + 255;
    //temp buffer for absolute files
    char* element_name = (char*)malloc(sizeof(char)*allocated);
#ifdef _WIN32
    WIN32_FIND_DATA element;
    HANDLE current_dir = INVALID_HANDLE_VALUE;
    FindFirstFile(absolute, &element);
    unsigned int allocated = len + 255;
    if(is_folder() && current_dir != INVALID_HANDLE_VALUE)
    {
        do
        {
            //name too long, reallocate the temp buffer
            if ((len+1+2+strlen(element.cFileName)) >= allocated)
            {
                free(element_name);
                allocated = len+1+2+(unsigned int)strlen(element.cFileName);
                element_name = (char*)malloc(sizeof(char)*allocated);
            }
            if(strcmp(element.cFileName, ".") != 0 &&
               strcmp(element.cFileName, "..") != 0)
            {
                strcpy(element_name, absolute);
                strcat(element_name, File::PATH_SEPARATOR_STRING);
                strcat(element_name, element.cFileName);
                retval->emplace_back(element_name);
            }
        }
        while(FindNextFile(current_dir, &element) != 0);
        FindClose(current_dir);
    }
#else
    DIR* current_dir;
    struct dirent* element;
    if(is_folder() && (current_dir = opendir(absolute)) != NULL)
    {
        while((element = readdir(current_dir)) != NULL)
        {
            //name too long, reallocate the temp buffer
            if((len+1+2+strlen(element->d_name))>=allocated)
            {
                free(element_name);
                allocated = len+1+2+(unsigned int)strlen(element->d_name);
                element_name = (char*)malloc(sizeof(char)*allocated);
            }
            //avoid listing . and ..
            if(strcmp(element->d_name, ".") != 0 &&
               strcmp(element->d_name, "..") != 0)
            {
                strcpy(element_name, absolute);
                strcat(element_name, File::PATH_SEPARATOR_STRING);
                strcat(element_name, element->d_name);
                retval->emplace_back(element_name);
            }
        }
        closedir(current_dir);
    }
#endif
    free(element_name);
}
