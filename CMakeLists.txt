cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(noise VERSION 0.0.0 LANGUAGES CXX)

add_subdirectory(external/cxxopts)
add_subdirectory(external/spdlog)

find_package(cxxopts)
find_package(spdlog)

file(GLOB SOURCES src/*.cpp)

add_executable(noise ${SOURCES})

target_link_libraries(noise cxxopts spdlog)