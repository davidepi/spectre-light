cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(spectre-light CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB spectre_core_sources
    src/geometry/*.cpp
    src/primitives/*.cpp
    src/accelerators/*.cpp
    src/samplers/*.cpp
    src/utility/*.cpp
    src/cameras/*.cpp
    src/materials/*.cpp)
file(GLOB spectre_core_headers
    src/settings.h
    src/validator.h
    src/localization.h
    src/geometry/*.hpp
    src/primitives/*.hpp
    src/accelerators/*.hpp
    src/samplers/*.hpp
    src/utility/*.hpp
    src/cameras/*.hpp
    src/materials/*.hpp)
include_directories(src)
include_directories(src/geometry)
include_directories(src/primitives)
include_directories(src/utility)
include_directories(src/accelerators)
include_directories(src/samplers)
include_directories(src/cameras)
include_directories(src/materials)
find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR})
endif(DOXYGEN_FOUND)

find_package(ImageMagick)
if(ImageMagick_FOUND)
    set_property(SOURCE src/cameras/image_output.cpp APPEND_STRING PROPERTY
        COMPILE_FLAGS " -DIMAGEMAGICK_FOUND ")
endif()

if(WIN32)
else()
    set_property(SOURCE src/utility/console.cpp APPEND_STRING PROPERTY
    COMPILE_FLAGS " -DSPECTRE_COLOURED_OUTPUT ")
endif()

add_executable(spectre src/main.cpp ${spectre_core_sources})

