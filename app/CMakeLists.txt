set(BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")

add_executable(noise app.cpp)

target_link_libraries(noise PRIVATE libnoise)

install(
    TARGETS
    libnoise
    ARCHIVE DESTINATION
    "${LIB_DIR}"
)

install(
    PROGRAMS
    "${PROJECT_BINARY_DIR}/noise"
    DESTINATION
    "${BIN_DIR}"
)