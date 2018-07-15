CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)
PROJECT(spectre-light C CXX)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
IF(MSVC)
    SET(CMAKE_C_FLAGS_DEBUG "/Wall /DDEBUG")
    SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    SET(CMAKE_C_FLAGS_RELEASE "/O2 /GR- /GS- /GL /Gw /Gy /MT /LTCG /w /DNDEBUG")
    SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
ELSE()
    SET(CMAKE_C_FLAGS_DEBUG "-O0 -pipe -fstack-protector -g -Wall -Wextra -Wpedantic -DDEBUG")
    SET(CMAKE_CXX_FLAGS_DEBUG  ${CMAKE_C_FLAGS_DEBUG})
    SET(CMAKE_C_FLAGS_RELEASE "-Ofast -pipe -flto -march=native -mtune=native -funroll-loops -fno-stack-protector -DNDEBUG")
    SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
ENDIF()

FILE(GLOB spectre_core_sources
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
     src/parsers/parser_obj.cpp
     src/utility/imageio/*.c)
FILE(GLOB spectre_test_sources
     tests/unit-testing/*.cpp
     )
FILE(GLOB spectre_distributions_sources
     tests/distributions/*.cpp
     )
INCLUDE_DIRECTORIES(src)
FIND_PACKAGE(Threads REQUIRED)

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    ADD_CUSTOM_TARGET(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(DOXYGEN_FOUND)

IF(NOT WIN32)
    SET_PROPERTY(SOURCE src/utility/console.cpp APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DSPECTRE_COLOURED_OUTPUT ")
ENDIF()

INCLUDE(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
IF(IS_BIG_ENDIAN)
    SET_PROPERTY(SOURCE src/utility/imageIO.cpp APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DIS_BIG_ENDIAN ")
ENDIF()

ADD_EXECUTABLE(spectre-full src/main.cpp ${spectre_core_sources})
TARGET_LINK_LIBRARIES(spectre-full ${CMAKE_THREAD_LIBS_INIT})
TARGET_COMPILE_DEFINITIONS(spectre-full PRIVATE SPECTRAL=1)

ADD_EXECUTABLE(spectre-rgb src/main.cpp ${spectre_core_sources})
TARGET_LINK_LIBRARIES(spectre-rgb ${CMAKE_THREAD_LIBS_INIT})

FIND_PACKAGE(ImageMagick COMPONENTS Magick++)
IF(ImageMagick_Magick++_FOUND)
    IF(ImageMagick_VERSION_STRING VERSION_LESS 7.0)
        MESSAGE(WARNING "Magick++ version should be greater than 7.0")
    ELSE()
        ADD_DEFINITIONS(" -DIMAGEMAGICK=\\\"${ImageMagick_Magick++_INCLUDE_DIRS}\\\" ")
        ADD_DEFINITIONS(" -DMAGICKCORE_QUANTUM_DEPTH=16 ")
        ADD_DEFINITIONS(" -DMAGICKCORE_HDRI_ENABLE=1 ")
        INCLUDE_DIRECTORIES(${ImageMagick_Magick++_INCLUDE_DIRS})
        TARGET_LINK_LIBRARIES(spectre-full ${ImageMagick_Magick++_LIBRARY})
        TARGET_LINK_LIBRARIES(spectre-rgb ${ImageMagick_Magick++_LIBRARY})
    ENDIF()
ENDIF(ImageMagick_Magick++_FOUND)
SET(CMAKE_VERBOSE_MAKEFILE ON)

FIND_PACKAGE(GTest)
IF(GTEST_FOUND)
    IF(CMAKE_BUILD_TYPE STREQUAL "Coverage")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    ENDIF(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
    ADD_EXECUTABLE(runTests EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/tests/allTests.cxx ${spectre_core_sources} ${spectre_test_sources})
    TARGET_LINK_LIBRARIES(runTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    SET_TARGET_PROPERTIES(runTests PROPERTIES COMPILE_FLAGS " -DTESTS -DDEBUG -DTEST_ASSETS=\\\"${CMAKE_CURRENT_SOURCE_DIR}/tests/assets/\\\"")
ENDIF(GTEST_FOUND)
IF(ImageMagick_Magick++_FOUND AND NOT ImageMagick_VERSION_STRING VERSION_LESS 7.0)
    TARGET_LINK_LIBRARIES(runTests ${ImageMagick_Magick++_LIBRARY})
ENDIF(ImageMagick_Magick++_FOUND AND NOT ImageMagick_VERSION_STRING VERSION_LESS 7.0)
FIND_PACKAGE(Gnuplot)
IF(GNUPLOT_FOUND)
    ADD_EXECUTABLE(distributions_data EXCLUDE_FROM_ALL ${spectre_distributions_sources} ${spectre_core_sources} ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/distributions_main.cpp)
    TARGET_COMPILE_DEFINITIONS(distributions_data PRIVATE SUPPRESS_MOTD=1)
    TARGET_LINK_LIBRARIES(distributions_data ${CMAKE_THREAD_LIBS_INIT})
    IF(ImageMagick_Magick++_FOUND AND NOT ImageMagick_VERSION_STRING VERSION_LESS 7.0)
        TARGET_LINK_LIBRARIES(distributions_data ${ImageMagick_Magick++_LIBRARY})
    ENDIF(ImageMagick_Magick++_FOUND AND NOT ImageMagick_VERSION_STRING VERSION_LESS 7.0)
    ADD_CUSTOM_COMMAND(OUTPUT filters_distributions.pdf primitives_distributions.pdf samplers_distributions.pdf materials_distributions.pdf microfacets_distributions.pdf
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
    ADD_CUSTOM_TARGET(distributions
                      DEPENDS filters_distributions.pdf
                      DEPENDS primitives_distributions.pdf
                      DEPENDS samplers_distributions.pdf
                      DEPENDS materials_distributions.pdf
                      DEPENDS microfacets_distributions.pdf)
ENDIF(GNUPLOT_FOUND)
