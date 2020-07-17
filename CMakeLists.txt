include(FetchContent)

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

project(
    noise
    VERSION 0.0.0
    DESCRIPTION "A visual entropy analysis tool"
    LANGUAGES CXX
)

configure_file(include/version.h.in version.h)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v2.2.0
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.7.0
)

FetchContent_MakeAvailable(cxxopts)
FetchContent_MakeAvailable(spdlog)

add_subdirectory(src)
add_subdirectory(app)