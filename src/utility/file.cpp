#include "file.hpp"
const char File::PATH_SEPARATOR = '/';
const char* File::CURRENT_DIR = realpath(".", NULL);
const size_t File::CURRENT_DIR_LEN = strlen(File::CURRENT_DIR);

File::File(const char* path)
{
    size_t pathlen = strlen(path);
    if(path[0]==File::PATH_SEPARATOR) //absolute, simply copy this path
    {
        absolute = (char*)malloc(sizeof(char)*(pathlen+1));
        strcpy(absolute,path);
        relative = absolute;
    }
    else //resolve the relative path
    {
        absolute = (char*)malloc(sizeof(char)*(CURRENT_DIR_LEN+1+pathlen+1));
        //TODO: need to think of a way to not use realpath again
        // --> manually resolve /../ and /./
        // -----> Also because realpath does not support non-existent files
    }
    
    File::statres = stat(absolute, &(File::fileinfo))==0;
    //path is a directory with the separator at the end
    if(absolute[pathlen-1]==File::PATH_SEPARATOR)
        absolute[--pathlen]=0; //decrease len and remove last char
    File::file = strrchr(absolute, File::PATH_SEPARATOR);
    //relative path
    if(file==NULL)
        file = absolute;
    else
        file+=1;
    File::ext = strrchr(file, '.');
    //set "" as extension instead of NULL if not found
    if(ext==NULL)
        ext = absolute+pathlen;
    else
        ext+=1;
    //hidden file with no extension
    if(ext==file+1)
        ext = absolute+pathlen;
}

File::File(const File& old_obj)
{
    File::absolute = (char*)malloc(sizeof(char)*(strlen(old_obj.absolute)+1));
    strcpy(absolute,old_obj.absolute);
    //recalculate offsets(since I cannot blindly copy pointers of other classes)
    File::relative = File::absolute+abs(old_obj.absolute-old_obj.relative);
    File::ext = File::ext+abs(old_obj.absolute-old_obj.ext);
    File::file = File::file+abs(old_obj.absolute-old_obj.file);
    File::statres = old_obj.statres;
    File::fileinfo = old_obj.fileinfo;
}

File::~File()
{
    free(File::absolute);
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
    return access(absolute, F_OK)==0;
}

bool File::readable()const
{
    return access(absolute, R_OK)==0;
}

bool File::writable()const
{
    return access(absolute, W_OK)==0;
}

bool File::is_absolute()const
{
    return relative[0]==PATH_SEPARATOR;
}

bool File::is_folder()const
{
    return statres && S_ISDIR(fileinfo.st_mode);
}

bool File::is_file()const
{
    return statres && S_ISREG(fileinfo.st_mode);
}
