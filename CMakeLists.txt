cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(noise VERSION 0.0.0 LANGUAGES CXX)

include_directories(include)

file(GLOB SOURCES src/*.cpp)

add_executable(noise ${SOURCES})