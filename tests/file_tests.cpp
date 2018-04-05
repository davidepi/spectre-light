
#include <gtest/gtest.h>


#include "utility/file.hpp"
#include <cstring>

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


