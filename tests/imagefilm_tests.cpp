
#include <gtest/gtest.h>


#include "cameras/image_film.hpp"
#include "samplers/box_filter.hpp"
#include "samplers/lanczos_filter.hpp"
#include <unistd.h>
TEST(ImageFilm,constructor)
{
    //another folder, fake file
    errors_count[CRITICAL_INDEX] = 0;
    ImageFilm img(2,2,"../folder/file.fake");
    EXPECT_EQ(errors_count[CRITICAL_INDEX], 1);
    errors_count[CRITICAL_INDEX] = 0;

    //another folder, writable, extension not ok
    ImageFilm img2(2,2,"./file.ok");
    BoxFilter filter(BOX_FILTER_EXTENT,BOX_FILTER_EXTENT);
    img2.set_filter(&filter);
    EXPECT_TRUE(img2.save_image());
    EXPECT_EQ(access("./file.ok.ppm",F_OK),0);
    unlink("./file.ok.ppm");

    //this folder, writable, extension ok
    ImageFilm img3(2,2,"file.ppm");
    img3.set_filter(&filter);
    EXPECT_TRUE(img3.save_image());
    EXPECT_EQ(access("file.ppm",F_OK),0);
    unlink("file.ppm");

    //another folder, no name provided
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img4(2,2,"./");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    img4.set_filter(&filter);
    EXPECT_TRUE(img4.save_image());
    EXPECT_EQ(access("./.ppm",F_OK),0);
    unlink("./.ppm");

    //almost similar extensions
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img5(2,2,"out.pph");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img5.save_image());
    EXPECT_EQ(access("out.pph.ppm",F_OK),0);
    unlink("out.pph.ppm");

    //bmp extension
    ImageFilm img6(2,2,"out.bmp");
    EXPECT_TRUE(img6.save_image());
    EXPECT_EQ(access("out.bmp",F_OK),0);
    unlink("out.bmp");

    //bmp similar extension
    errors_count[WARNING_INDEX] = 0;
    ImageFilm img7(2,2,"out.bmm");
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
    EXPECT_TRUE(img7.save_image());
    EXPECT_EQ(access("out.bmm.ppm",F_OK),0);
    unlink("out.bmm.ppm");
}

TEST(ImageFilm,add_pixel)
{
    ImageFilm img(800,600,"out.ppm");
    LanczosFilter filter(LANCZOS_FILTER_EXTENT,LANCZOS_FILTER_EXTENT,3);
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
    img.add_pixel(&sample, ColorXYZ(1,1,1), &secure_area);
    //assert that the pixel has not been deferred
    EXPECT_TRUE(secure_area.deferred.empty());

    //add pixel in the area where another thread could interfere,
    //various combinations
    //ytop xleft corner
    sample.posx = 32.5f;
    sample.posy = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ytop xcenter
    sample.posy = 32.5f;
    sample.posx = 48.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ytop xright
    sample.posy = 32.5f;
    sample.posx = 63.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ycenter xleft
    sample.posy = 48.5f;
    sample.posx = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ycenter xright
    sample.posy = 48.5f;
    sample.posx = 63.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ybot xleft
    sample.posy = 63.5f;
    sample.posx = 32.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ybot xcenter
    sample.posy = 63.5f;
    sample.posx = 48.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());
    //ybot xright
    sample.posy = 63.5f;
    sample.posx = 63.5f;
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());
    secure_area.deferred = std::stack<TodoPixel>();
    EXPECT_TRUE(secure_area.deferred.empty());

    EXPECT_TRUE(img.save_image());
    EXPECT_EQ(access("out.ppm",F_OK),0);
    unlink("out.ppm");
}

TEST(ImageFilm,add_pixel_deferred)
{
    //TODO: maybe add real threads
    ImageFilm img(800,600,"out.ppm");
    LanczosFilter filter(LANCZOS_FILTER_EXTENT,LANCZOS_FILTER_EXTENT,3);
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
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());

    img.add_pixel_deferred(&secure_area);
    EXPECT_TRUE(secure_area.deferred.empty());
}

TEST(ImageFilm,add_pixel_forced)
{
    //TODO: maybe add real threads
    ImageFilm img(800,600,"out.ppm");
    LanczosFilter filter(LANCZOS_FILTER_EXTENT,LANCZOS_FILTER_EXTENT,3);
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
    img.add_pixel(&sample, ColorXYZ(-1,-1,-1),&secure_area);
    EXPECT_FALSE(secure_area.deferred.empty());

    img.add_pixel_forced(&secure_area);
    EXPECT_TRUE(secure_area.deferred.empty());
}

