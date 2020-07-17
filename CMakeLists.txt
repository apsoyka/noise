cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(Noise VERSION 0.0.0 DESCRIPTION "A visual entropy analysis tool" LANGUAGES CXX)

configure_file(include/version.h.in version.h)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

add_subdirectory(external/cxxopts)
add_subdirectory(external/spdlog)

find_package(cxxopts)
find_package(spdlog)

add_subdirectory(src)
add_subdirectory(app)