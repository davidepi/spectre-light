#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#else

#include <gtest/gtest.h>

#endif

SPECTRE_TEST_INIT(File_tests)

#include "utility/file.hpp"
#include <cstring>

SPECTRE_TEST(File, absolute_path)
{
    const char* cur_dir = realpath(".", NULL);
    char* path = (char*)malloc(sizeof(char)*(strlen(cur_dir)+64+1));
    //normal file appended
    strcpy(path, cur_dir);
    strcat(path, "/file.jpg");
    File f0("file.jpg");
    EXPECT_STREQ(f0.absolute_path(), path);
    //file starting with ./
    File f1("./file.jpg");
    EXPECT_STREQ(f1.absolute_path(), path);
    //file ending with /
    File f2("./file.jpg/");
    EXPECT_STREQ(f2.absolute_path(), path);
    //multiple /./ in the name
    File f3("./././file.jpg");
    EXPECT_STREQ(f3.absolute_path(), path);
    //file with ../ in the name
    File f4("folder/../file.jpg");
    EXPECT_STREQ(f4.absolute_path(), path);
    //too many ../
    File f5("../../../../../../../../../../../file.jpg");
    EXPECT_STREQ(f5.absolute_path(), "/file.jpg");
    //double slash used
    strcpy(path, cur_dir);
    strcat(path, "/folder/file.jpg");
    File f6("folder//file.jpg");
    EXPECT_STREQ(f6.absolute_path(), path);
    // /./ in the path
    File f7("folder/./file.jpg");
    EXPECT_STREQ(f7.absolute_path(), path);
    //absolute path
    strcpy(path, "/var/tmp/values");
    File f8(path);
    EXPECT_STREQ(f8.absolute_path(), path);
    //absolute path with double slash
    strcpy(path, "/var/tmp/values");
    File f9("//var/tmp//values/");
    EXPECT_STREQ(f9.absolute_path(), path);
    //root
    File f10("/");
    EXPECT_STREQ(f10.absolute_path(), "/");
    //ending with /.
    File f11("./.");
    EXPECT_STREQ(f11.absolute_path(), cur_dir);
    //ending with /..
    File f12("folder/..");
    EXPECT_STREQ(f12.absolute_path(), cur_dir);
    free(path);
    free((void*)cur_dir);
}

SPECTRE_TEST(File, extension)
{
    //normal execution
    File f0("file.jpg");
    EXPECT_STREQ(f0.extension(), "jpg");
    //no extension
    File f1("file");
    EXPECT_STREQ(f1.extension(), "");
    //extension in hidden file
    File f2(".a.out");
    EXPECT_STREQ(f2.extension(), "out");
    //hidden file with no extension
    File f3(".bashrc");
    EXPECT_STREQ(f3.extension(), "");
    //ending with point
    File f4(".a.out.");
    EXPECT_STREQ(f4.extension(), "");
    //folder
    File f5("/absolute/folder/file.ext");
    EXPECT_STREQ(f5.extension(), "ext");
    //folder with separator
    File f6("/absolute/folder/");
    EXPECT_STREQ(f6.extension(), "");
    //root
    File f7("/");
    EXPECT_STREQ(f7.extension(), "");
}

SPECTRE_TEST(File, filename)
{
    //normal execution
    File f0("file.jpg");
    EXPECT_STREQ(f0.filename(), "file.jpg");
    //relative folder
    File f1("./file.jpg");
    EXPECT_STREQ(f1.filename(), "file.jpg");
    //absolute folder
    File f2("/root/file.jpg");
    EXPECT_STREQ(f2.filename(), "file.jpg");
    //folder only
    File f3("/root/folder");
    EXPECT_STREQ(f3.filename(), "folder");
    //folder only with separator
    File f4("/root/folder/");
    EXPECT_STREQ(f4.filename(), "folder");
    //root
    File f5("/");
    EXPECT_STREQ(f5.filename(), "/");
    File f6("/file");
    EXPECT_STREQ(f6.filename(), "file");
}

SPECTRE_TEST(File, exists)
{
    //not existent
    File f0("nonexistent.jpg");
    EXPECT_FALSE(f0.exists());
    //existent
    File f1(TEST_ASSETS "images/wrong_magic1.ppm");
    EXPECT_TRUE(f1.exists());
}

SPECTRE_TEST(File, readable)
{
    //not existent so -> not readable
    File f0("nonexistent.jpg");
    EXPECT_FALSE(f0.readable());
    //readable
    File f1(TEST_ASSETS "images/wrong_magic1.ppm");
    EXPECT_TRUE(f1.readable());
}

SPECTRE_TEST(File, writable)
{
    //not existent and multipath so -> not readable
    File f0("/root/wrong_folder/nonexistent.jpg");
    EXPECT_FALSE(f0.writable());
    //writable
    File f1(TEST_ASSETS);
    EXPECT_TRUE(f1.writable());
}

SPECTRE_TEST(File, copy_constructor)
{
    File f1("folder/../file.jpg");
    File f2(f1);
    EXPECT_STREQ(f1.filename(), f2.filename());
    EXPECT_STREQ(f1.extension(), f2.extension());
    EXPECT_STREQ(f1.absolute_path(), f2.absolute_path());
}

SPECTRE_TEST(File, is_folder)
{
    //nonexistent
    File f1("non existent");
    EXPECT_FALSE(f1.is_folder());
    //existent but not folder
    File f2(TEST_ASSETS "wrong_magic1.ppm");
    EXPECT_FALSE(f2.is_folder());
    //existent and folder
    File f3(TEST_ASSETS);
    EXPECT_TRUE(f3.is_folder());
}

SPECTRE_TEST(File, is_file)
{
    //nonexistent
    File f1("non existent");
    EXPECT_FALSE(f1.is_file());
    //existent but not file
    File f2(TEST_ASSETS "images/wrong_magic1.ppm");
    EXPECT_TRUE(f2.is_file());
    //existent and file
    File f3(TEST_ASSETS);
    EXPECT_FALSE(f3.is_file());
}

SPECTRE_TEST(File, copy_assignment)
{
    File f1("folder/../file.jpg");
    File f2 = f1;
    EXPECT_STREQ(f1.filename(), f2.filename());
    EXPECT_STREQ(f1.extension(), f2.extension());
    EXPECT_STREQ(f1.absolute_path(), f2.absolute_path());
}

SPECTRE_TEST(File, get_parent)
{
    File f1(TEST_ASSETS);
    File f2(TEST_ASSETS "folder");
    File f3 = f2.get_parent();
    EXPECT_STREQ(f3.extension(), f1.extension());
    EXPECT_STREQ(f3.filename(), f1.filename());
    EXPECT_STREQ(f3.absolute_path(), f1.absolute_path());

    //1 folder over root
    File f4("/folder");
    File f5 = f4.get_parent();
    EXPECT_STREQ(f5.extension(), "");
    EXPECT_STREQ(f5.filename(), "/");
    EXPECT_STREQ(f5.absolute_path(), "/");

    //root
    File f6("/");
    File f7 = f6.get_parent();
    EXPECT_STREQ(f7.extension(), "");
    EXPECT_STREQ(f7.filename(), "/");
    EXPECT_STREQ(f7.absolute_path(), "/");
}

SPECTRE_TEST(File, assignment_operator)
{
    File f1("folder/../file.jpg");
    File f2 = f1;
    EXPECT_STREQ(f1.filename(), f2.filename());
    EXPECT_STREQ(f1.extension(), f2.extension());
    EXPECT_STREQ(f1.absolute_path(), f2.absolute_path());
}

SPECTRE_TEST(File, mkdir)
{
    bool res;
    //try to create already existing folder
    File f1(TEST_ASSETS);
    EXPECT_TRUE(f1.exists());
    res = f1.mkdir();
    EXPECT_FALSE(res);
    //create new folder
    const char* foldername = TEST_ASSETS "folder";
    File f2(foldername);
    EXPECT_FALSE(f2.exists());
    res = f2.mkdir();
    EXPECT_TRUE(res);
    EXPECT_TRUE(f2.exists());

    rmdir(foldername);
}

SPECTRE_TEST(File, mkdirs)
{
    bool res;
    //not enough permissions
    File f1("/root/impossible");
    res = f1.mkdirs();
    EXPECT_FALSE(res);

    //already existing
    File f2(TEST_ASSETS);
    res = f2.mkdirs();
    EXPECT_FALSE(res);

    //quick execution
    File f3(TEST_ASSETS "testfolder1");
    res = f3.mkdirs();
    EXPECT_TRUE(res);
    EXPECT_EQ(rmdir(TEST_ASSETS
                      "testfolder1"), 0);

    //multiple creations
    File f4(TEST_ASSETS "testfolder1/testfolder2");
    res = f4.mkdir();
    EXPECT_FALSE(res);
    res = f4.mkdirs();
    EXPECT_TRUE(res);
    EXPECT_EQ(rmdir(TEST_ASSETS
                      "testfolder1/testfolder2"), 0);
    EXPECT_EQ(rmdir(TEST_ASSETS
                      "testfolder1"), 0);
}

SPECTRE_TEST(File, ls)
{
    std::vector<File> res;

    //non existent
    File f1("/root/kjhgufydt");
    f1.ls(&res);
    EXPECT_TRUE(res.empty());

    File f2(TEST_ASSETS);
    f2.ls(&res);
    EXPECT_EQ(res.size(), 3);
}

SPECTRE_TEST(File, append)
{
    File f1(TEST_ASSETS);
    f1.append("images/flipped.bmp");
    EXPECT_TRUE(f1.exists());
    f1.append("non-existend");
    EXPECT_FALSE(f1.exists());

    File f2(TEST_ASSETS "/parser");
    f2.append("..//./images/./correct.bmp");
    EXPECT_TRUE(f2.exists());
    f2.append("../");
    EXPECT_TRUE(f2.is_folder());
    f2.append(".bashrc");
    EXPECT_STREQ(f2.extension(), "");
}

SPECTRE_TEST(File, is_absolute)
{
    EXPECT_TRUE(is_absolute("/path"));
    EXPECT_FALSE(is_absolute("../path"));
}

SPECTRE_TEST_END(File_tests)
