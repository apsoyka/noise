cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(noise VERSION 0.0.0 LANGUAGES CXX)

add_subdirectory(external/cxxopts)

find_package(cxxopts)

file(GLOB SOURCES src/*.cpp)

add_executable(noise ${SOURCES})

target_link_libraries(noise cxxopts)