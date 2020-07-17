file(GLOB HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(libnoise ${SOURCES} ${HEADERS})

target_include_directories(libnoise PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})

target_link_libraries(libnoise PRIVATE cxxopts spdlog)

source_group(TREE ${CMAKE_SOURCE_DIR}/include FILES ${HEADERS})