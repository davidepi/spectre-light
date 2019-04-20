# EVERY COMMENT IN THIS FILE WILL BE WRITTEN IN CAPS LOCK
CMAKE_MINIMUM_REQUIRED(VERSION 3.10 FATAL_ERROR)
PROJECT(spectre-light C CXX)
SET(CMAKE_C_STANDARD 90) #ANSI C
SET(CMAKE_CXX_STANDARD 11) #C++11
SET(CMAKE_CXX_STANDARD_REQUIRED ON) #ENFORCE PREVIOUS LINES
SET(CMAKE_VERBOSE_MAKEFILE ON)
IF(MSVC)
    SET(CMAKE_C_FLAGS_DEBUG "/Wall /DDEBUG")
    SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    SET(CMAKE_C_FLAGS_RELEASE "/O2 /GR- /GS- /GL /Gw /Gy /MT /LTCG /w /DNDEBUG")
    SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
ELSE()
    SET(CMAKE_C_FLAGS_DEBUG "-O0 -pipe -fstack-protector -g -Wall -Wextra -Wpedantic -DDEBUG ")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    SET(CMAKE_C_FLAGS_RELEASE "-Ofast -pipe -flto -march=native -mtune=native -fno-stack-protector -DNDEBUG")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-rtti -fno-exceptions")
ENDIF()

#CORE FILES
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
     src/parsers/config_parser.tab.c
     src/parsers/lex.yy.c
     src/parsers/parsed_structs.c
     src/parsers/*.cpp
     src/utility/imageio/*.c)
FILE(GLOB spectre_test_sources
     tests/unit-testing/*.cpp
     )
FILE(GLOB spectre_distributions_sources
     tests/distributions/*.cpp
     )
#EVERYTHING IS INCLUDED STARTING FROM SRC
INCLUDE_DIRECTORIES(src)
#I NEED THREADS
FIND_PACKAGE(Threads REQUIRED)

#DOCUMENTATION
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    IF(DOXYGEN_DOT_FOUND)
        ADD_CUSTOM_TARGET(doc ${CMAKE_COMMAND} -E env DOXYGEN_DOT=YES ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR})
    ELSE(DOXYGEN_DOT_FOUND)
        ADD_CUSTOM_TARGET(doc ${CMAKE_COMMAND} -E env DOXYGEN_DOT=NO ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR})
    ENDIF(DOXYGEN_DOT_FOUND)
ENDIF(DOXYGEN_FOUND)

IF(NOT WIN32)
    SET_PROPERTY(SOURCE src/utility/console.cpp APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DSPECTRE_COLOURED_OUTPUT ")
ENDIF()

#YET ANOTHER CHECK TO BE SURE OF THE SYSTEM ENDIANNESS
INCLUDE(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
IF(IS_BIG_ENDIAN)
    SET_PROPERTY(SOURCE src/utility/imageio/imageio.c APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DIS_BIG_ENDIAN ")
    SET_PROPERTY(SOURCE src/textures/image_map.cpp APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DIS_BIG_ENDIAN ")
    SET_PROPERTY(SOURCE src/textures/texture_image.cpp APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DIS_BIG_ENDIAN ")
ENDIF()

#CORE EXECUTABLES
ADD_EXECUTABLE(spectre-full src/main.cpp ${spectre_core_sources})
TARGET_LINK_LIBRARIES(spectre-full ${CMAKE_THREAD_LIBS_INIT})
TARGET_COMPILE_DEFINITIONS(spectre-full PRIVATE SPECTRAL=1)
ADD_EXECUTABLE(spectre-rgb src/main.cpp ${spectre_core_sources})
TARGET_LINK_LIBRARIES(spectre-rgb ${CMAKE_THREAD_LIBS_INIT})

#PRINTING COMPILER INFO IS ABSOLUTELY NECESSARY
SET_PROPERTY(TARGET spectre-full spectre-rgb APPEND_STRING PROPERTY COMPILE_FLAGS " -DCOMPILER_NAME=\\\"${CMAKE_CXX_COMPILER_ID}\\\" -DCOMPILER_VERSION=\\\"${CMAKE_CXX_COMPILER_VERSION}\\\" ")

#TESTING FRAMEWORK FOUND
FIND_PACKAGE(GTest)
IF(GTEST_FOUND)
    ENABLE_TESTING()
    IF(CMAKE_BUILD_TYPE STREQUAL "Coverage")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    ENDIF(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
    ADD_EXECUTABLE(runTests EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/tests/allTests.cxx ${spectre_core_sources} ${spectre_test_sources})
    TARGET_LINK_LIBRARIES(runTests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    SET_TARGET_PROPERTIES(runTests PROPERTIES COMPILE_FLAGS " -DTESTS -DDEBUG -DTEST_ASSETS=\\\"${CMAKE_CURRENT_SOURCE_DIR}/tests/assets/\\\"")
    SET_PROPERTY(TARGET runTests APPEND_STRING PROPERTY COMPILE_FLAGS " -DCOMPILER_NAME=\\\"${CMAKE_CXX_COMPILER_ID}\\\" -DCOMPILER_VERSION=\\\"${CMAKE_CXX_COMPILER_VERSION}\\\" ")
    GTEST_DISCOVER_TESTS(runTests AUTO)
ENDIF(GTEST_FOUND)

#ADD TARGET TO PLOT SOME FANCY DISTRIBUTIONS
FIND_PACKAGE(Gnuplot)
IF(GNUPLOT_FOUND)
    ADD_EXECUTABLE(distributions_data EXCLUDE_FROM_ALL ${spectre_distributions_sources} ${spectre_core_sources} ${CMAKE_CURRENT_SOURCE_DIR}/tests/distributions/distributions_main.cpp)
    TARGET_COMPILE_DEFINITIONS(distributions_data PRIVATE SUPPRESS_MOTD=1)
    TARGET_LINK_LIBRARIES(distributions_data ${CMAKE_THREAD_LIBS_INIT})
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

#ADD SUPPORT FOR JPEG IMAGES, ALSO TO THE TESTS
FIND_PACKAGE(JPEG)
IF(JPEG_FOUND)
    INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
    SET_PROPERTY(SOURCE src/utility/imageio/imageio.c APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DJPEG_FOUND ")
    SET_PROPERTY(SOURCE src/utility/imageio/io_jpg.c APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DJPEG_FOUND ")
    TARGET_LINK_LIBRARIES(spectre-full ${JPEG_LIBRARIES})
    TARGET_LINK_LIBRARIES(spectre-rgb ${JPEG_LIBRARIES})
    IF(GTEST_FOUND)
        SET_PROPERTY(SOURCE tests/unit-testing/imageio_tests.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DJPEG_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/imagefilm_tests.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DJPEG_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/io_jpg.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DJPEG_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/io_jpg_tests.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DJPEG_FOUND ")
        TARGET_LINK_LIBRARIES(runTests ${JPEG_LIBRARIES})
    ENDIF(GTEST_FOUND)
    IF(GNUPLOT_FOUND)
        TARGET_LINK_LIBRARIES(distributions_data ${JPEG_LIBRARIES})
    ENDIF(GNUPLOT_FOUND)
ENDIF(JPEG_FOUND)

#ADD SUPPORT FOR PNG IMAGES, ALSO TO THE TESTS. THIS IS COPIED FROM ABOVE
FIND_PACKAGE(PNG)
IF(PNG_FOUND)
    INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR})
    SET_PROPERTY(SOURCE src/utility/imageio/imageio.c APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DPNG_FOUND ")
    SET_PROPERTY(SOURCE src/utility/imageio/io_png.c APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DPNG_FOUND ")
    TARGET_LINK_LIBRARIES(spectre-full ${PNG_LIBRARIES})
    TARGET_LINK_LIBRARIES(spectre-rgb ${PNG_LIBRARIES})
    IF(GTEST_FOUND)
        SET_PROPERTY(SOURCE tests/unit-testing/imageio_tests.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DPNG_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/imagefilm_tests.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DPNG_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/io_png.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DPNG_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/io_png.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DPNG_FOUND ")
        TARGET_LINK_LIBRARIES(runTests ${PNG_LIBRARIES})
    ENDIF(GTEST_FOUND)
    IF(GNUPLOT_FOUND)
        TARGET_LINK_LIBRARIES(distributions_data ${PNG_LIBRARIES})
    ENDIF(GNUPLOT_FOUND)
ENDIF(PNG_FOUND)

#ADD SUPPORT FOR TIFF IMAGES, ALSO TO THE TESTS. THIS IS COPIED FROM ABOVE
FIND_PACKAGE(TIFF)
IF(TIFF_FOUND)
    INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIR})
    SET_PROPERTY(SOURCE src/utility/imageio/imageio.c APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DTIFF_FOUND ")
    SET_PROPERTY(SOURCE src/utility/imageio/io_tiff.c APPEND_STRING PROPERTY
                 COMPILE_FLAGS " -DTIFF_FOUND ")
    TARGET_LINK_LIBRARIES(spectre-full ${TIFF_LIBRARIES})
    TARGET_LINK_LIBRARIES(spectre-rgb ${TIFF_LIBRARIES})
    IF(GTEST_FOUND)
        SET_PROPERTY(SOURCE tests/unit-testing/imageio_tests.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DTIFF_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/imagefilm_tests.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DTIFF_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/io_tiff.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DTIFF_FOUND ")
        SET_PROPERTY(SOURCE tests/unit-testing/io_tiff.cpp APPEND_STRING
                     PROPERTY COMPILE_FLAGS " -DTIFF_FOUND ")
        TARGET_LINK_LIBRARIES(runTests ${TIFF_LIBRARIES})
    ENDIF(GTEST_FOUND)
    IF(GNUPLOT_FOUND)
        TARGET_LINK_LIBRARIES(distributions_data ${TIFF_LIBRARIES})
    ENDIF(GNUPLOT_FOUND)
ENDIF(TIFF_FOUND)

EXECUTE_PROCESS(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_BRANCH_RETCODE
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

EXECUTE_PROCESS(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_COMMIT_HASH_RETCODE
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

EXECUTE_PROCESS(
    COMMAND git rev-list --count HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_COMMIT_NO_RETCODE
    OUTPUT_VARIABLE GIT_COMMIT_NO
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

IF(${GIT_BRANCH_RETCODE} STREQUAL "0" AND ${GIT_COMMIT_HASH_RETCODE} STREQUAL "0" AND ${GIT_COMMIT_NO_RETCODE} STREQUAL "0")
    SET_PROPERTY(TARGET spectre-full spectre-rgb APPEND_STRING PROPERTY COMPILE_FLAGS " -DGIT_BRANCH=\\\"${GIT_BRANCH}\\\" -DGIT_COMMIT_HASH=\\\"${GIT_COMMIT_HASH}\\\" -DGIT_COMMIT_NO=\\\"${GIT_COMMIT_NO}\\\" ")
ENDIF()
