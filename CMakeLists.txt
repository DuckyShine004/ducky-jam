cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ducky_jam VERSION 0.0.1)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/fmt")

# Find all source files
file(GLOB_RECURSE DUCKY_JAM_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

find_package(fmt REQUIRED)
# find_package(OpenAL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SNDFILE REQUIRED sndfile)

add_executable(ducky_jam ${DUCKY_JAM_SOURCES})

target_include_directories(ducky_jam
    PRIVATE
    ${OPENAL_INCLUDE_DIRS}
    ${SNDFILE_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(ducky_jam
    PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(ducky_jam
    PRIVATE
    glfw
    fmt::fmt
    ${OPENAL_LDFLAGS}
    ${SNDFILE_LDFLAGS}
)
