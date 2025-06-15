cmake_minimum_required(VERSION 3.10)

project(ducky_jam VERSION 0.0.1)

# Find all source files
file(GLOB_RECURSE DUCKY_JAM_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_executable(ducky_jam ${DUCKY_JAM_SOURCES})

target_include_directories(ducky_jam
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(ducky_jam
    PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(ducky_jam
    PRIVATE
    glfw
)
