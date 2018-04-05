#include "file.hpp"
const char File::PATH_SEPARATOR = '/';
File::File(const char* path)
{
    size_t pathlen = strlen(path);
    File::fullpath = (char*)malloc(sizeof(char)*pathlen+1);
    strcpy(fullpath,path);
    //path is a directory with the separator at the end
    if(fullpath[pathlen-1]==File::PATH_SEPARATOR)
        fullpath[--pathlen]=0; //decrease len and remove last char
    File::file = strrchr(fullpath, File::PATH_SEPARATOR);
    //relative path
    if(file==NULL)
        file = fullpath;
    else
        file+=1;
    File::ext = strrchr(file, '.');
    //set "" as extension instead of NULL if not found
    if(ext==NULL)
        ext = fullpath+pathlen;
    else
        ext+=1;
    //hidden file with no extension
    if(ext==file+1)
        ext = fullpath+pathlen;
}

File::~File()
{
    free(File::fullpath);
}

const char* File::extension()const
{
    return File::ext;
}

const char* File::filename()const
{
    return File::file;
}

bool File::exists()const
{
    return access(fullpath, F_OK)==0;
}

bool File::readable()const
{
    return access(fullpath, R_OK)==0;
}

bool File::writable()const
{
    return access(fullpath, W_OK)==0;
}
