cmake_minimum_required(VERSION 2.8)
project(spectre-light)
if(CMAKE_VERSION VERSION_LESS "3.1") #ensure c++11, not default if cxx is clang
    set(CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
file(GLOB spectre_core_sources
    src/geometry/*.cpp
    src/primitives/*.cpp
    src/utility/*.cpp)
file(GLOB spectre_core_headers
    src/settings.h
    src/validator.h
    src/geometry/*.hpp
    src/primitives/*.hpp
    src/utility/*.hpp)
include_directories(src)
include_directories(src/geometry)
include_directories(src/primitives)
include_directories(src/utility)
find_package(Doxygen)

if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR})
endif(DOXYGEN_FOUND)

add_executable(spectre src/main.cpp ${spectre_core_sources})
