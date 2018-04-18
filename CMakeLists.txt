cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(spectre-light C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/Wall /DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /GR- /GS- /GL /Gw /Gy /MT /LTCG /w /DNDEBUG")
else()
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -pipe -fstack-protector -g -Wall -Wextra -Wpedantic -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -pipe -flto -march=native -mtune=native -funroll-loops -fno-stack-protector -DNDEBUG")
endif()

file(GLOB spectre_core_sources
    src/lights/*.cpp
    src/renderer.cpp
    src/geometry/*.cpp
    src/primitives/*.cpp
    src/accelerators/*.cpp
    src/samplers/*.cpp
    src/utility/*.cpp
    src/cameras/*.cpp
    src/integrators/*.cpp
    src/textures/*.cpp
    src/materials/*.cpp
    src/parsers/config_parser.tab.cc
    src/parsers/lex.yy.cc
    src/parsers/config_driver.cpp
    src/parsers/parser_obj.cpp)
file(GLOB spectre_test_sources
    tests/*.cpp
    )
file(GLOB spectre_distributions_sources
    tests/distributions/*.cpp
    )
include_directories(src)
find_package (Threads REQUIRED)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR})
endif(DOXYGEN_FOUND)

if(NOT WIN32)
    set_property(SOURCE src/utility/console.cpp APPEND_STRING PROPERTY
        COMPILE_FLAGS " -DSPECTRE_COLOURED_OUTPUT ")
endif()

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    set_property(SOURCE src/utility/imageIO.cpp APPEND_STRING PROPERTY
        COMPILE_FLAGS " -DIS_BIG_ENDIAN ")
endif()

add_executable(spectre-full src/main.cpp ${spectre_core_sources})
target_link_libraries (spectre-full ${CMAKE_THREAD_LIBS_INIT})
target_compile_definitions (spectre-full PRIVATE SPECTRAL=1)

add_executable(spectre-rgb src/main.cpp ${spectre_core_sources})
target_link_libraries (spectre-rgb ${CMAKE_THREAD_LIBS_INIT})

find_package(ImageMagick COMPONENTS Magick++)
if(ImageMagick_Magick++_FOUND)
  add_definitions(" -DIMAGEMAGICK=\\\"${ImageMagick_Magick++_INCLUDE_DIRS}\\\" ")
  add_definitions(" -DMAGICKCORE_QUANTUM_DEPTH=16 ")
  add_definitions(" -DMAGICKCORE_HDRI_ENABLE=1 ")
  include_directories(${ImageMagick_Magick++_INCLUDE_DIRS})
  target_link_libraries(spectre-full ${ImageMagick_Magick++_LIBRARY})
  target_link_libraries(spectre-rgb ${ImageMagick_Magick++_LIBRARY})
endif(ImageMagick_Magick++_FOUND)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(GTest)
if(GTEST_FOUND)
    if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    endif(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(runTests EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/tests/allTests.cxx ${spectre_core_sources} ${spectre_test_sources})
    target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    set_target_properties(runTests PROPERTIES COMPILE_FLAGS " -DTESTS -DDEBUG -DTEST_ASSETS=\\\"${CMAKE_CURRENT_SOURCE_DIR}/tests/assets/\\\"")
endif(GTEST_FOUND)
if(ImageMagick_Magick++_FOUND)
  target_link_libraries(runTests ${ImageMagick_Magick++_LIBRARY})
endif(ImageMagick_Magick++_FOUND)
find_package(Gnuplot)
if(GNUPLOT_FOUND)
    add_executable(distributions_data EXCLUDE_FROM_ALL ${spectre_distributions_sources} ${spectre_core_sources} ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/distributions_main.cpp)
    target_compile_definitions(distributions_data PRIVATE SUPPRESS_MOTD=1)
if(ImageMagick_Magick++_FOUND)
  target_link_libraries(distributions_data ${ImageMagick_Magick++_LIBRARY})
endif(ImageMagick_Magick++_FOUND)
    add_custom_command(OUTPUT filters_distributions.pdf primitives_distributions.pdf samplers_distributions.pdf materials_distributions.pdf microfacets_distributions.pdf
        DEPENDS distributions_data
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/data
        COMMAND distributions_data ${CMAKE_CURRENT_BINARY_DIR}/data
        COMMENT "Plotting distributions"
        COMMAND ${GNUPLOT_EXECUTABLE} -e "path='${CMAKE_CURRENT_BINARY_DIR}/data/'" ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/filters_gnuplot.txt
        COMMAND ${GNUPLOT_EXECUTABLE} -e "path='${CMAKE_CURRENT_BINARY_DIR}/data/'" ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/primitives_gnuplot.txt
        COMMAND ${GNUPLOT_EXECUTABLE} -e "path='${CMAKE_CURRENT_BINARY_DIR}/data/'" ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/samplers_gnuplot.txt
        COMMAND ${GNUPLOT_EXECUTABLE} -e "path='${CMAKE_CURRENT_BINARY_DIR}/data/'" ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/materials_gnuplot.txt
        COMMAND ${GNUPLOT_EXECUTABLE} -e "path='${CMAKE_CURRENT_BINARY_DIR}/data/'" ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/microfacets_gnuplot.txt
        VERBATIM)
add_custom_target(distributions 
    DEPENDS filters_distributions.pdf
    DEPENDS primitives_distributions.pdf
    DEPENDS samplers_distributions.pdf
    DEPENDS materials_distributions.pdf
    DEPENDS microfacets_distributions.pdf)
endif(GNUPLOT_FOUND)
