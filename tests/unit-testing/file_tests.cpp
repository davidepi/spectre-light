#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "windows.h"
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "utility/file.hpp"
#include <cstring>

SPECTRE_TEST_INIT(File_tests)

SPECTRE_TEST(File, absolute_path)
{
    char* cur_dir;
    int cur_dir_len;
#ifdef _WIN32
    cur_dir_len = GetFullPathNameA(".", 0, NULL, NULL);
    cur_dir = (char*)malloc(sizeof(char)*(cur_dir_len + 1));
    GetFullPathNameA(".", cur_dir_len + 1, cur_dir, NULL);
#else
    cur_dir = realpath(".", NULL);
    cur_dir_len = (int)strlen(cur_dir);
#endif
    char* path = (char*)malloc(sizeof(char)*(strlen(cur_dir)+64+1));
    //normal file appended
    strcpy(path, cur_dir);
    strcat(path, File::PATH_SEPARATOR_STRING);
    strcat(path, "file.jpg");
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
#ifdef _WIN32
    EXPECT_STREQ(f5.absolute_path(), "C:\\file.jpg");
#else
    EXPECT_STREQ(f5.absolute_path(), "/file.jpg");
#endif
    //double slash used
    strcpy(path, cur_dir);
    strcat(path, File::PATH_SEPARATOR_STRING);
    strcat(path, "folder");
    strcat(path, File::PATH_SEPARATOR_STRING);
    strcat(path, "file.jpg");
    File f6("folder//file.jpg");
    EXPECT_STREQ(f6.absolute_path(), path);
    // /./ in the path
    File f7("folder/./file.jpg");
    EXPECT_STREQ(f7.absolute_path(), path);
    //absolute path
#ifdef _WIN32
    strcpy(path, "C:\\file\\var\\file.jpg");
#else
    strcpy(path, "/var/tmp/values");
#endif
    File f8(path);
    EXPECT_STREQ(f8.absolute_path(), path);
    //absolute path with double slash
#ifdef _WIN32
    File f9("C:\\\\file\\\\var\\\\file.jpg");
#else
    File f9("//var/tmp//values/");
#endif
    EXPECT_STREQ(f9.absolute_path(), path);
    //root
#ifdef _WIN32
    File f10("C:\\");
    EXPECT_STREQ(f10.absolute_path(), "C:\\");
    //f8 f9 and f10 with UNC absolute paths
    strcpy(path, "\\\\file\\var\\file.jpg");
    File f8unc("\\\\file\\var\\file.jpg");
    EXPECT_STREQ(f8unc.absolute_path(), path);
    File f9unc("\\\\\\\\file\\\\var\\\\file.jpg");
    EXPECT_STREQ(f9unc.absolute_path(), path);
    File f10unc("\\\\");
    EXPECT_STREQ(f10unc.absolute_path(), "\\\\");
#else
    File f10("/");
    EXPECT_STREQ(f10.absolute_path(), "/");
#endif
    //ending with /.
    File f11("./.");
    EXPECT_STREQ(f11.absolute_path(), cur_dir);
    //ending with /..
    File f12("folder/..");
    EXPECT_STREQ(f12.absolute_path(), cur_dir);
    //windows path, run also on *nix
    strcpy(path, cur_dir);
    strcat(path, File::PATH_SEPARATOR_STRING);
    strcat(path, "folder");
    strcat(path, File::PATH_SEPARATOR_STRING);
    strcat(path, "file.jpg");
    File f13("folder\\file.jpg");
    EXPECT_STREQ(f13.absolute_path(), path);
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
    //windows path for everyone
    File fwin("folder\\.a.out");
    EXPECT_STREQ(fwin.extension(), "out");
#ifdef _WIN32
    //folder
    File f5("C:\\absolute/folder/file.ext");
    EXPECT_STREQ(f5.extension(), "ext");
    File f5unc("\\\\absolute/folder/file.ext");
    EXPECT_STREQ(f5unc.extension(), "ext");
    //folder with separator
    File f6("C:\\absolute/folder/");
    EXPECT_STREQ(f6.extension(), "");
    File f6unc("\\\\absolute/folder/");
    EXPECT_STREQ(f6unc.extension(), "");
    //root
    File f7("C:\\");
    EXPECT_STREQ(f7.extension(), "");
    File f7unc("\\\\");
    EXPECT_STREQ(f7unc.extension(), "");
#else
    //folder
    File f5("/absolute/folder/file.ext");
    EXPECT_STREQ(f5.extension(), "ext");
    //folder with separator
    File f6("/absolute/folder/");
    EXPECT_STREQ(f6.extension(), "");
    //root
    File f7("/");
    EXPECT_STREQ(f7.extension(), "");
#endif
}

SPECTRE_TEST(File, filename)
{
    //normal execution
    File f0("file.jpg");
    EXPECT_STREQ(f0.filename(), "file.jpg");
    //relative folder
    File f1("./file.jpg");
    EXPECT_STREQ(f1.filename(), "file.jpg");
#ifdef _WIN32
    //absolute folder
    File f2("C:\\root/file.jpg");
    EXPECT_STREQ(f2.filename(), "file.jpg");
    File f2unc("\\\\root/file.jpg");
    EXPECT_STREQ(f2unc.filename(), "file.jpg");
    //folder only
    File f3("C:\\root/folder");
    EXPECT_STREQ(f3.filename(), "folder");
    File f3unc("\\\\root/folder");
    EXPECT_STREQ(f3unc.filename(), "folder");
    //folder only with separator
    File f4("C:\\root/folder/");
    EXPECT_STREQ(f4.filename(), "folder");
    File f4unc("\\\\root/folder/");
    EXPECT_STREQ(f4unc.filename(), "folder");
    //root
    File f5("C:\\");
    EXPECT_STREQ(f5.filename(), "C:\\");
    File f5unc("\\\\");
    EXPECT_STREQ(f5unc.filename(), "\\\\");
    File f6("C:\\file");
    EXPECT_STREQ(f6.filename(), "file");
    File f6unc("\\\\file");
    EXPECT_STREQ(f6unc.filename(), "file");
#else
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
#endif
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
#ifdef _WIN32
    //1 folder over root
    File f4("C:\\folder");
    File f5 = f4.get_parent();
    EXPECT_STREQ(f5.extension(), "");
    EXPECT_STREQ(f5.filename(), "C:\\");
    EXPECT_STREQ(f5.absolute_path(), "C:\\");

    //root
    File f6("C:\\");
    File f7 = f6.get_parent();
    EXPECT_STREQ(f7.extension(), "");
    EXPECT_STREQ(f7.filename(), "C:\\");
    EXPECT_STREQ(f7.absolute_path(), "C:\\");

    //1 folder over root
    File f4unc("\\\\folder");
    File f5unc = f4unc.get_parent();
    EXPECT_STREQ(f5unc.extension(), "");
    EXPECT_STREQ(f5unc.filename(), "\\\\");
    EXPECT_STREQ(f5unc.absolute_path(), "\\\\");

    //root
    File f6unc("\\\\");
    File f7unc = f6unc.get_parent();
    EXPECT_STREQ(f7unc.extension(), "");
    EXPECT_STREQ(f7unc.filename(), "\\\\");
    EXPECT_STREQ(f7unc.absolute_path(), "\\\\");
#else
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
#endif
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
    ASSERT_TRUE(res);
    ASSERT_TRUE(f2.exists());

#ifdef _WIN32
    EXPECT_TRUE(RemoveDirectoryA(foldername));
#else
    EXPECT_EQ(rmdir(foldername), 0);
#endif

}

SPECTRE_TEST(File, mkdirs)
{
    bool res;
    //not enough permissions
#ifdef _WIN32
    File f1("C:\\Windows");
#else
    File f1("/root/impossible");
#endif
    res = f1.mkdirs();
    EXPECT_FALSE(res);
    //already existing
    File f2(TEST_ASSETS);
    res = f2.mkdirs();
    EXPECT_FALSE(res);
    //quick execution
    File f3(TEST_ASSETS "testfolder1");
    res = f3.mkdirs();
    ASSERT_TRUE(res);
    ASSERT_TRUE(f3.exists());
#ifdef _WIN32
    EXPECT_TRUE(RemoveDirectoryA(TEST_ASSETS "testfolder1"));
#else
    EXPECT_EQ(rmdir(TEST_ASSETS
                      "testfolder1"), 0);
#endif
    //multiple creations
    File f4(TEST_ASSETS "testfolder1/testfolder2");
    res = f4.mkdir();
    EXPECT_FALSE(res);
    res = f4.mkdirs();
    ASSERT_TRUE(res);
    ASSERT_TRUE(f4.exists());
#ifdef _WIN32
    EXPECT_TRUE(RemoveDirectoryA(TEST_ASSETS "testfolder1\\testfolder2"));
    EXPECT_TRUE(RemoveDirectoryA(TEST_ASSETS "testfolder1"));
#else
    EXPECT_EQ(rmdir(TEST_ASSETS
                      "testfolder1/testfolder2"), 0);
    EXPECT_EQ(rmdir(TEST_ASSETS
                      "testfolder1"), 0);
#endif
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

    File fwin(TEST_ASSETS);
    fwin.append("parser\\..\\\\.\\images\\.\\correct.bmp");
    EXPECT_TRUE(fwin.exists());
    fwin.append("..\\");
    EXPECT_TRUE(fwin.is_folder());
    fwin.append(".bashrc");
    EXPECT_STREQ(fwin.extension(), "");

}

SPECTRE_TEST(File, list_files)
{
    std::vector<File> res;

    //non existent
    File f1("/root/kjhgufydt");
    f1.ls(&res);
    EXPECT_TRUE(res.empty());

    File f2(TEST_ASSETS);
    f2.ls(&res);
    EXPECT_EQ(res.size(), (size_t)4);
}

SPECTRE_TEST(File, is_absolute_inline)
{
#ifdef _WIN32
    EXPECT_TRUE(is_absolute("C:\\path"));
    EXPECT_TRUE(is_absolute("\\\\path"));
    EXPECT_FALSE(is_absolute("/path"));
    EXPECT_FALSE(is_absolute("../path"));
#else
    EXPECT_TRUE(is_absolute("/path"));
    EXPECT_FALSE(is_absolute("C:\\path"));
    EXPECT_FALSE(is_absolute("\\\\path"));
    EXPECT_FALSE(is_absolute("../path"));
#endif
}

SPECTRE_TEST_END(File_tests)
