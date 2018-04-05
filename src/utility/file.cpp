#include "file.hpp"

File::File(const char* path)
{
    File::filename = (const char*)malloc(sizeof(char)*strlen(path));
    File::extension = strrchr(filename, '.');
    //set "" as extension instead of NULL if not found
    if(extension==NULL)
        extension = filename+strlen(filename)-1;
    strcpy(filename,path);
}

File::~File()
{
    free(File::filename);
}

bool File::exists()const
{
    return access(filename, F_OK);
}

bool File::can_read()const
{
    return access(filename, R_OK);
}

bool File::can_write()const
{
    return access(filename, W_OK);
}
