# spectre-light
>Yet another photorealistic renderer with great ambitions

![render-example](https://github.com/davidepi/spectre-light/blob/master/docs/readme_image.jpg)

[![](https://img.shields.io/github/release/davidepi/spectre-light.svg)](https://github.com/davidepi/spectre-light/releases)
[![Build status](https://travis-ci.org/davidepi/spectre-light.svg?branch=master)](https://travis-ci.org/davidepi/spectre-light)
[![Build status](https://ci.appveyor.com/api/projects/status/d4bx9kjo42nnpfy5/branch/master?svg=true)](https://ci.appveyor.com/project/darkstar13/spectre-light/branch/master)
[![codecov](https://codecov.io/gh/davidepi/spectre-light/branch/master/graph/badge.svg)](https://codecov.io/gh/davidepi/spectre-light)
[![loc](https://tokei.rs/b1/github/davidepi/spectre-light)](https://github.com/davidepi/spectre-light)

*spectre-light* is a photorealistic unbiased physically-based renderer. It inherits its base
structure from the great [pbrt](http://pbrt.org "pbrt homepage") by M.Pharr, W. Jakob and G.
Humphreys, but it is slowly diverging from it. The long term goal of this project is a
GPU-based physically based renderer, however, in order to reach that point, first a solid CPU
renderer will be created and then GPU support will be added.

The road ahead is long and for this reason the file [Roadmap.md](./Roadmap.md) contains the
list of features that will be implemented during the way

## Getting started

These instruction will get you a running copy of *spectre-light* in your machine in the fastest
possible way.

*spectre-light* uses [cmake](https://cmake.org "cmake homepage") as a build system, so this
is the only mandatory dependency. This tool is available in almost every package manager
if you are running a Linux distribution, as well as in `brew` if you are running macOS.
Furthermore, you can download the Windows or macOS installer of cmake from the official
site

### Dependencies

Although no dependency is strictly required, with the exception of [cmake](https://cmake.org "cmake homepage"),
having the Magick++ library is stronly suggested (API version 7.0 or newer). The Magick++ lib is part of the
[ImageMagick](https://www.imagemagick.org/script/index.php) suite and can be easily installed
in any OS. Without Magick++, *spectre-light* is limited to read and write only NetPBM and
Windows Bitmap V3.0 files.

### Building

Building *spectre-light* works exactly like any other cmake project.
Here are the instructions step by step, assuming cmake 3.1+ and the build tools (build-essential, Xcode command line tools or Visual Studio) are already installed

#### Linux and macOS
```
mkdir build/
cd build
cmake -DCMAKE_BUILD_TYPE="Release" ..
make
```

#### Windows
```
md build\
cd build
cmake -G "Visual Studio XX 20XX Win64" ..
```
where the visual studio values can be
- `Visual Studio 10 2010 Win64` for Visual Studio 2010
- `Visual Studio 11 2012 Win64` for Visual Studio 2012
- `Visual Studio 12 2013 Win64` for Visual Studio 2013
- `Visual Studio 14 2015 Win64` for Visual Studio 2015
- `Visual Studio 15 2017 Win64` for Visual Studio 2017

At this point you need to open the generated solution and compile all targets with visual
studio. Be sure to use a Release configuration for 64 bit

### Running

After building *spectre-light* you can run it with the following command
```
spectre-rgb input.txt
```
or with
```
spectre-full input.txt
```

`input.txt` is an ASCII file containing the description of the scene that will be rendered

## Input

The input file format is explained [here](./src/parsers/README.md).

*spectre-light* supports `.obj` files for scene and models,  `.ppm` and `.bmp` for textures. As already said, if Magick++ is
available, additional image formats such as `.jpg`, `.tiff`, `.tga`, `.dds` and `.png` are available.
`.mtl` is not available as an obj companion file for materials due to its tremendous binding with the Phong illumination model. Check the section *Missing .mtl* of the aforementioned input readme for more informations .

 ## Documentation

 This project uses [Doxygen](http://doxygen.org) in order to generate the documentation.
 If you have doxygen installed, cmake will detect it and produce the target `doc`. After
 that the only thing left to do is to invoke the following command
 ```
 make doc
 ```
 in order to generate the html documentation of the project

 ## Tests

 Unit testing is done with [Google Test](https://github.com/google/googletest) and
 thus it is required as additional dependency. In order to run the tests the following
 commands have to be issued
 ```
 mkdir build_tests/
 cd build_tests/
 cmake -DCMAKE_BUILD_TYPE="Coverage" ..
 make runTests
 ```

 Then, running the newly created executable `runTests` will run every test
 in the suite.

 If [gnuplot](http://www.gnuplot.info/) is also installed, the target `make distributions`
 will generate some pdfs with the distributions of the various sampling routines.


 Unfortunately, for now, tests work only on Linux and macOS
 ## License
 
 *spectre-light* is released under the terms of the GNU GPLv3 License. You may find the
 content of the license in the [LICENSE.txt](./LICENSE.txt) file.
 
 The images in this README are rendered with models courtesy of the [Stanford scanning
 repository](http://graphics.stanford.edu/data/3Dscanrep/)
