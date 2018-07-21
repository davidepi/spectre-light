#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#include <unistd.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#include <io.h>
#include <direct.h>
#define unlink _unlink
#define access _access
#define rmdir _rmdir
#define F_OK 0x0
#else

#include <gtest/gtest.h>
#include <unistd.h>

#endif

#include "cameras/image_film.hpp"
#include "samplers/filter_box.hpp"
#include "samplers/filter_lanczos.hpp"

SPECTRE_TEST_INIT(ImageFilm_tests)

SPECTRE_TEST(ImageFIlm, constructor)
{
    //this test was made when the extension was checked by hand letter by letter
    //now is mostly useless

    //another folder, fake file
    errors_count[CRITICAL_INDEX] = 0;
    ImageFilm img(2, 2, "../folder/file.fake");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;

    //another folder, writable, extension not ok
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img2(2, 2, "./file.ok");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    FilterBox filter;
    img2.set_filter(&filter);
    EXPECT_TRUE(img2.save_image());
    EXPECT_EQ(access("file.ok.ppm", F_OK), 0);
    EXPECT_EQ(unlink("file.ok.ppm"), 0);

    //this folder, writable, extension ok
    ImageFilm img3(2, 2, "file.ppm");
    img3.set_filter(&filter);
    EXPECT_TRUE(img3.save_image());
    EXPECT_EQ(access("file.ppm", F_OK), 0);
    EXPECT_EQ(unlink("file.ppm"), 0);

    //another folder, no name provided
    errors_count[CRITICAL_INDEX] = 0;
    ImageFilm img4(2, 2, "./");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;

    //after adding automatic extension, a folder is referenced
    File folder("folder.ppm");
    bool res = folder.mkdir();
    EXPECT_TRUE(res);
    errors_count[CRITICAL_INDEX] = 0;
    ImageFilm img5(2, 2, "folder");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;
    EXPECT_EQ(rmdir(folder.absolute_path()), 0);

    //almost similar extensions
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img6(2, 2, "out.pph");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img6.save_image());
    EXPECT_EQ(access("out.pph.ppm", F_OK), 0);
    EXPECT_EQ(unlink("out.pph.ppm"), 0);

    //bmp extension
    ImageFilm img7(2, 2, "out.bmp");
    EXPECT_TRUE(img7.save_image());
    EXPECT_EQ(access("out.bmp", F_OK), 0);
    EXPECT_EQ(unlink("out.bmp"), 0);

    //bmp similar extension
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img8(2, 2, "out.bmm");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img8.save_image());
    EXPECT_EQ(access("out.bmm.ppm", F_OK), 0);
    EXPECT_EQ(unlink("out.bmm.ppm"), 0);

    //jpg correctly saved
#ifdef JPEG_FOUND
    ImageFilm img9(2, 2, "out.jpg");
    EXPECT_TRUE(img9.save_image());
    EXPECT_EQ(access("out.jpg", F_OK), 0);
    EXPECT_EQ(unlink("out.jpg"), 0);
    ImageFilm img10(2, 2, "out.jpeg");
    EXPECT_TRUE(img10.save_image());
    EXPECT_EQ(access("out.jpeg", F_OK), 0);
    EXPECT_EQ(unlink("out.jpeg"), 0);
#else
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img9(2,2,"out.jpg");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img9.save_image());
    EXPECT_EQ(access("out.jpg.ppm",F_OK),0);
    EXPECT_EQ(unlink("out.jpg.ppm"),0);
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img10(2,2,"out.jpeg");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img10.save_image());
    EXPECT_EQ(access("out.jpeg.ppm",F_OK),0);
    EXPECT_EQ(unlink("out.jpeg.ppm"),0);
#endif
    //png correctly saved
#ifdef PNG_FOUND
    ImageFilm img11(2, 2, "out.png");
    EXPECT_TRUE(img11.save_image());
    EXPECT_EQ(access("out.png", F_OK), 0);
    EXPECT_EQ(unlink("out.png"), 0);
#else
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img11(2,2,"out.png");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img11.save_image());
    EXPECT_EQ(access("out.png.ppm",F_OK),0);
    EXPECT_EQ(unlink("out.png.ppm"),0);
#endif
    //tiff correctly saved
#ifdef TIFF_FOUND
    ImageFilm img12(2, 2, "out.tif");
    EXPECT_TRUE(img12.save_image());
    EXPECT_EQ(access("out.tif", F_OK), 0);
    EXPECT_EQ(unlink("out.tif"), 0);
    ImageFilm img13(2, 2, "out.tiff");
    EXPECT_TRUE(img13.save_image());
    EXPECT_EQ(access("out.tiff", F_OK), 0);
    EXPECT_EQ(unlink("out.tiff"), 0);
#else
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img12(2,2,"out.tif");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img12.save_image());
    EXPECT_EQ(access("out.tif.ppm",F_OK),0);
    EXPECT_EQ(unlink("out.tif.ppm"),0);
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img13(2,2,"out.tiff");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img13.save_image());
    EXPECT_EQ(access("out.tiff.ppm",F_OK),0);
    EXPECT_EQ(unlink("out.tiff.ppm"),0);
#endif
}

SPECTRE_TEST(ImageFIlm, add_pixel)
{
    ImageFilm img(800, 600, "out.ppm");
    FilterLanczos filter(3);
    img.set_filter(&filter);
    ExecutorData secure_area;
    secure_area.startx = 32;
    secure_area.endx = 64;
    secure_area.starty = 32;
    secure_area.endy = 64;
    EXPECT_TRUE(secure_area.deferred.empty());

    //add pixel in the secure area
    Sample sample;
    sample.posx = 48.5f;
    sample.posy = 48.5f;
    img.add_pixel(&sample, ColorXYZ(1, 1, 1), &secure_area);
    //assert that the pixel has not been deferred
    EXPECT_TRUE(secure_area.deferred.empty());

    //add pixel in the area where another thread could interfere,
    //various combinations
    //ytop xleft corner
    sample.posx = 32.5f;
    sample.posy = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ytop xcenter
    sample.posy = 32.5f;
    sample.posx = 48.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ytop xright
    sample.posy = 32.5f;
    sample.posx = 63.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ycenter xleft
    sample.posy = 48.5f;
    sample.posx = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ycenter xright
    sample.posy = 48.5f;
    sample.posx = 63.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ybot xleft
    sample.posy = 63.5f;
    sample.posx = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ybot xcenter
    sample.posy = 63.5f;
    sample.posx = 48.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ybot xright
    sample.posy = 63.5f;
    sample.posx = 63.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());

    EXPECT_TRUE(img.save_image());
    EXPECT_EQ(access("out.ppm", F_OK), 0);
    EXPECT_EQ(unlink("out.ppm"), 0);
}

SPECTRE_TEST(ImageFIlm, add_pixel_deferred)
{
    //TODO: maybe add real threads
    ImageFilm img(800, 600, "out.ppm");
    FilterLanczos filter(3);
    img.set_filter(&filter);
    ExecutorData secure_area;
    secure_area.startx = 32;
    secure_area.endx = 64;
    secure_area.starty = 32;
    secure_area.endy = 64;
    EXPECT_TRUE(secure_area.deferred.empty());
    Sample sample;

    //generate deferred data
    sample.posx = 32.5f;
    sample.posy = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());

    img.add_pixel_deferred(&secure_area);
    EXPECT_TRUE(secure_area.deferred.empty());
}

SPECTRE_TEST(ImageFIlm, add_pixel_forced)
{
    //TODO: maybe add real threads
    ImageFilm img(800, 600, "out.ppm");
    FilterLanczos filter(3);
    img.set_filter(&filter);
    ExecutorData secure_area;
    secure_area.startx = 32;
    secure_area.endx = 64;
    secure_area.starty = 32;
    secure_area.endy = 64;
    EXPECT_TRUE(secure_area.deferred.empty());
    Sample sample;

    //generate deferred data
    sample.posx = 32.5f;
    sample.posy = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1, -1, -1), &secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());

    img.add_pixel_forced(&secure_area);
    EXPECT_TRUE(secure_area.deferred.empty());
}

SPECTRE_TEST_END(ImageFilm_tests)
