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
        int i=-1;
        //copy everything inside the buffer but skip duplicated separators
        while(path[++i]!=0)
        {
            if(path[i]==File::PATH_SEPARATOR && path[i+1]==File::PATH_SEPARATOR)
                continue;
            else
                absolute[i] = path[i];
        }
    }
    else //resolve the relative path
    {
        absolute = (char*)malloc(sizeof(char)*(CURRENT_DIR_LEN+1+pathlen+1));
        strcpy(absolute, CURRENT_DIR);
        int absolute_index = (int)CURRENT_DIR_LEN;
        int relative_index = 0;
        if(path[0]=='.')
        {
            //resolve ../file
            if(path[1]=='.' && path[2]==File::PATH_SEPARATOR)
            {
                relative_index = 3;
                //backtrack to previous / in the absolute path
                //(guaranteed to exists since file is absolute)
                while(absolute[absolute_index]!=File::PATH_SEPARATOR &&
                      absolute_index>0)
                    absolute_index--;
            }
            else if(path[1]==File::PATH_SEPARATOR) //resolve ./file
                relative_index=2;
        }
        absolute[absolute_index++]=File::PATH_SEPARATOR;
        /*
         *  at this point
         *  -> relative path does not start with . (checked in this if)
         *  -> relative path does not starts with /
         *  -> absolute path ends with /
         */
        while(relative_index<pathlen)
        {
            if(path[relative_index]==File::PATH_SEPARATOR)
            {
                if(path[relative_index+1]=='.')
                {
                    //handle /./
                    if(path[relative_index+2]==File::PATH_SEPARATOR)
                    {
                        relative_index+=2;
                        continue;
                    }
                    //handle /../
                    else if(path[relative_index+2]=='.' &&
                            path[relative_index+3]==File::PATH_SEPARATOR)
                    {
                        relative_index+=3;
                        absolute_index-=2;
                        while(absolute[absolute_index--]!=PATH_SEPARATOR &&
                              absolute_index>0);
                        continue;
                    }
                }
                //handle //
                else if(path[relative_index+1]==File::PATH_SEPARATOR)
                {
                    relative_index++;
                    continue;
                }
            }
            absolute[absolute_index++] = path[relative_index++];
        }
        absolute[absolute_index]=0;
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

bool File::is_folder()const
{
    return statres && S_ISDIR(fileinfo.st_mode);
}

bool File::is_file()const
{
    return statres && S_ISREG(fileinfo.st_mode);
}
