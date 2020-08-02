set(BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")

add_executable(noise app.cpp)

set_target_properties(
    libnoise
    PROPERTIES
    OUTPUT_NAME
    "noise"
)

target_link_libraries(noise PRIVATE libnoise)

install(
    TARGETS
    libnoise
    ARCHIVE
    DESTINATION
    "${LIB_DIR}"
)

install(
    TARGETS
    noise
    RUNTIME
    DESTINATION
    "${BIN_DIR}"
)