//author: Davide Pizzolotto
//license: GNU GPLv3

#include "file.hpp"

const char File::PATH_SEPARATOR = '/';
const char* File::PATH_SEPARATOR_STRING = "/";

File::File(const char* path)
{
    int pathlen = (int)strlen(path);
    if(path[0]==File::PATH_SEPARATOR) //absolute, simply copy this path
    {
        absolute = (char*)malloc(sizeof(char)*(pathlen+1));
        int relative_index=0;
        int absolute_index=0;
        //copy everything inside the buffer but skip duplicated separators
        while(path[relative_index]!=0)
        {
            if(path[relative_index]==File::PATH_SEPARATOR && path[relative_index+1]==File::PATH_SEPARATOR)
            {
                relative_index++;
                continue;
            }
            else
                absolute[absolute_index++] = path[relative_index++];
        }
        //remove last trailing char, if exists and not the root trailing
        if(absolute[absolute_index-1]==File::PATH_SEPARATOR && absolute_index>1)
            absolute_index--;
        absolute[absolute_index] = 0;
    }
    else //resolve the relative path
    {
        const char* CURRENT_DIR = realpath(".", NULL);
        const size_t CURRENT_DIR_LEN = strlen(CURRENT_DIR);
        absolute = (char*)malloc(sizeof(char)*(CURRENT_DIR_LEN+1+pathlen+1));
        strcpy(absolute, CURRENT_DIR);
        int absolute_index = (int)CURRENT_DIR_LEN;
        int relative_index = 0;
        if(path[0]=='.')
        {
            //resolve ../file
            if(path[1]=='.' && path[2]==File::PATH_SEPARATOR)
            {
                relative_index = 2;
                //backtrack to previous / in the absolute path
                //(guaranteed to exists since file is absolute)
                //position right on / ready to be substituted
                while(absolute_index-->0 &&
                      absolute[absolute_index]!=File::PATH_SEPARATOR);
            }
            else if(path[1]==File::PATH_SEPARATOR) //resolve ./file
                relative_index=1;
        }
        if(path[relative_index]!=File::PATH_SEPARATOR)
            absolute[absolute_index++]=File::PATH_SEPARATOR;
        /*
         *  at this point
         *  -> relative path does not start with . (checked in this if)
         *  -> relative starts with / or a filename
         *  -> absolute path ends with / if relative does not starts with /
         */
        while(relative_index<pathlen)
        {
            if(path[relative_index]==File::PATH_SEPARATOR)
            {
                if(path[relative_index+1]=='.')
                {
                    //handle /./
                    if(path[relative_index+2]==File::PATH_SEPARATOR ||
                       path[relative_index+2]==0)
                    {
                        relative_index+=2;
                        continue;
                    }
                    //handle /../
                    else if(path[relative_index+2]=='.' &&
                            (path[relative_index+3]==File::PATH_SEPARATOR ||
                             path[relative_index+3]==0))
                    {
                        relative_index+=3;
                        //avoid out of bounds if too many ../../../
                        if(absolute_index<=1)
                            continue;
                        absolute_index-=2;
                        while(absolute_index-->0 &&
                              absolute[absolute_index]!=PATH_SEPARATOR);
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
        //remove last trailing char, if exists and not root trailing
        if(absolute[absolute_index-1]==File::PATH_SEPARATOR && absolute_index>1)
            absolute_index--;
        absolute[absolute_index]=0;
        free((void*)CURRENT_DIR);
    }
    File::statres = stat(absolute, &(File::fileinfo))==0;
    //guaranteed to exists at least the toplevel /
    File::file = strrchr(absolute, File::PATH_SEPARATOR);
    //not /
    if(*(file+1)!=0)
        File::file++;
    File::ext = strrchr(file, '.');
    //set "" as extension instead of NULL if not found
    if(ext==NULL)
        ext = absolute+strlen(absolute);
    else
        ext+=1;
    //hidden file w/o extension (separate case because on windows does not hold)
    if(ext==file+1)
        ext = absolute+strlen(absolute);
}

File::File(const File& old_obj)
{
    File::absolute = (char*)malloc(sizeof(char)*(strlen(old_obj.absolute)+1));
    strcpy(absolute,old_obj.absolute);
    //recalculate offsets(since I cannot blindly copy pointers of other classes)
    File::ext = File::absolute+(old_obj.ext-old_obj.absolute);
    File::file = File::absolute+(old_obj.file-old_obj.absolute);
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

const char* File::absolute_path()const
{
    return File::absolute;
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

File& File::operator=(const File &old)
{
    File::absolute = (char*)malloc(sizeof(char)*(strlen(old.absolute)+1));
    strcpy(absolute,old.absolute);
    //recalculate offsets(since I cannot blindly copy pointers of other classes)
    File::ext = File::absolute+(old.ext-old.absolute);
    File::file = File::absolute+(old.file-old.absolute);
    File::statres = old.statres;
    File::fileinfo = old.fileinfo;
    return *this;
}

File File::get_parent()const
{
    File retval(*this);
    if(retval.file[0]!='/') //not root
    {
        int i = -1;
        //starts from -1 up to - max_decrement
        int max_decrement = (int)(absolute-file);
        //root folder is the parent
        if(max_decrement==-1)
        {
            retval.absolute[1]=0;
            retval.file = retval.absolute;
            retval.ext = retval.absolute+1;
        }
        //replace the / right before the filename with 0
        else
        {
            retval.absolute[(retval.file-retval.absolute)-1]=0;
            //update the extension to be "" -> point to the newly inserted 0
            retval.ext=retval.file-1;
            //go back with the file pointer until the last /
            while(i-->max_decrement && file[i]!=File::PATH_SEPARATOR);
            //if not root, point to the filename
            if(i!=max_decrement)
                retval.file+=i+1;
            //else
                /* do nothing, already catched in the max_decrement==-1 */;
        }
    }
    return retval;
}

bool File::mkdir()
{
    bool retval = ::mkdir(absolute,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)==0;
    //refresh info about this folder
    File::statres = stat(absolute, &(File::fileinfo))==0;
    return retval;
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
            while(index++<len && absolute[index]!=File::PATH_SEPARATOR);
            absolute[index]=0;
            if(access(absolute, F_OK)!=0) //folder does not exist
            {
                res = File::mkdir();
                created = true;
            }
            //resume searching
            absolute[index]=File::PATH_SEPARATOR;
            if(!res)
                return false;
        }
    }
    else
        created = true;
    //no need to refresh informations since is done by the mkdir() function
    return created;
}

void File::ls(std::vector<File>* retval)const
{
    DIR* current_dir;
    unsigned int len = (unsigned int)strlen(absolute);
    unsigned int allocated = len+255;
    struct dirent* element;
    if(is_folder() && (current_dir = opendir(absolute))!=NULL)
    {
        //temp buffer
        char* element_name = (char*)malloc(sizeof(char)*allocated);
        while((element = readdir(current_dir))!=NULL)
        {
            //name too long, reallocate the temp buffer
            if((len+1+1+strlen(element->d_name))>=allocated)
            {
                free(element_name);
                allocated = len+1+1+(unsigned int)strlen(element->d_name);
                element_name = (char*)malloc(sizeof(char)*allocated);
            }
            //avoid listing . and ..
            if(strcmp(element->d_name,"." )!=0 &&
               strcmp(element->d_name,"..")!=0 )
            {
                strcpy(element_name, absolute);
                strcat(element_name,File::PATH_SEPARATOR_STRING);
                strcat(element_name,element->d_name);
                retval->emplace_back(element_name);
            }
        }
        free(element_name);
        closedir(current_dir);
    }
}
