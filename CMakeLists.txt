cmake_minimum_required(VERSION 2.8)
project(spectre-light)
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
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR})
endif(DOXYGEN_FOUND)

add_executable(spectre src/main.cpp ${spectre_core_sources})
