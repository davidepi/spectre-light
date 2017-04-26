cmake_minimum_required(VERSION 2.8)
project(spectre-light)
file(GLOB spectre_core_sources
    src/geometry/*.cpp
    src/utility/*.cpp)
file(GLOB spectre_core_headers
    src/geometry/*.hpp
    src/utility/*.hpp)
include_directories(src)
include_directories(src/geometry)
include_directories(src/utility)
add_executable(spectre src/main.cpp ${spectre_core_sources})
