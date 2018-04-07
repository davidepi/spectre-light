
#include <gtest/gtest.h>


#include "utility/file.hpp"
#include <cstring>

TEST(File,absolute_path)
{
    char* path = (char*)malloc(sizeof(char)*(File::CURRENT_DIR_LEN+64+1));
    //normal file appended
    strcpy(path, File::CURRENT_DIR);
    strcat(path,"/file.jpg");
    File f0("file.jpg");
    EXPECT_EQ(strcmp(f0.absolute_path(),path), 0);
    //file starting with ./
    File f1("./file.jpg");
    EXPECT_EQ(strcmp(f1.absolute_path(),path), 0);
    //file ending with /
    File f2("./file.jpg/");
    EXPECT_EQ(strcmp(f2.absolute_path(),path), 0);
    //multiple /./ in the name
    File f3("./././file.jpg");
    EXPECT_EQ(strcmp(f3.absolute_path(),path), 0);
    //file with ../ in the name
    File f4("folder/../file.jpg");
    EXPECT_EQ(strcmp(f4.absolute_path(),path), 0);
    //too many ../
    File f5("../../../../../../../../../../../file.jpg");
    EXPECT_EQ(strcmp(f5.absolute_path(),"/file.jpg"), 0);
    //double slash used
    strcpy(path, File::CURRENT_DIR);
    strcat(path,"/folder/file.jpg");
    File f6("folder//file.jpg");
    EXPECT_EQ(strcmp(f6.absolute_path(),path), 0);
    // /./ in the path
    File f7("folder/./file.jpg");
    EXPECT_EQ(strcmp(f7.absolute_path(),path), 0);
    //absolute path
    strcpy(path,"/var/tmp/values");
    File f8(path);
    EXPECT_EQ(strcmp(f8.absolute_path(),path),0);
    //absolute path with double slash
    strcpy(path,"/var/tmp/values");
    File f9("//var/tmp//values/");
    EXPECT_EQ(strcmp(f9.absolute_path(),path),0);
    free(path);
}

TEST(File,extension)
{
    //normal execution
    File f0("file.jpg");
    EXPECT_EQ(strcmp(f0.extension(),"jpg"),0);
    //no extension
    File f1("file");
    EXPECT_EQ(strcmp(f1.extension(),""),0);
    //extension in hidden file
    File f2(".a.out");
    EXPECT_EQ(strcmp(f2.extension(),"out"),0);
    //hidden file with no extension
    File f3(".bashrc");
    EXPECT_EQ(strcmp(f3.extension(),""),0);
    //ending with point
    File f4(".a.out.");
    EXPECT_EQ(strcmp(f4.extension(),""),0);
    //folder
    File f5("/absolute/folder/file.ext");
    EXPECT_EQ(strcmp(f5.extension(),"ext"),0);
    //folder with separator
    File f6("/absolute/folder/");
    EXPECT_EQ(strcmp(f6.extension(),""),0);
}

TEST(File,filename)
{
    //normal execution
    File f0("file.jpg");
    EXPECT_EQ(strcmp(f0.filename(),"file.jpg"),0);
    //relative folder
    File f1("./file.jpg");
    EXPECT_EQ(strcmp(f1.filename(),"file.jpg"),0);
    //absolute folder
    File f2("/root/file.jpg");
    EXPECT_EQ(strcmp(f2.filename(),"file.jpg"),0);
    //folder only
    File f3("/root/folder");
    EXPECT_EQ(strcmp(f3.filename(),"folder"),0);
    //folder only with separator
    File f4("/root/folder/");
    EXPECT_EQ(strcmp(f4.filename(),"folder"),0);
}

TEST(File,exists)
{
    //not existent
    File f0("nonexistent.jpg");
    EXPECT_FALSE(f0.exists());
    //existent
    File f1(TEST_ASSETS "wrong_magic1.ppm");
    EXPECT_TRUE(f1.exists());
}

TEST(File,readable)
{
    //not existent so -> not readable
    File f0("nonexistent.jpg");
    EXPECT_FALSE(f0.readable());
    //readable
    File f1(TEST_ASSETS "wrong_magic1.ppm");
    EXPECT_TRUE(f1.readable());
}

TEST(File,writable)
{
    //not existent and multipath so -> not readable
    File f0("/root/wrong_folder/nonexistent.jpg");
    EXPECT_FALSE(f0.writable());
    //writable
    File f1(TEST_ASSETS);
    EXPECT_TRUE(f1.writable());
}


