cmake_minimum_required(VERSION 3.0.0)
project(ducky_jam VERSION 0.0.1)

add_executable(ducky_jam
    src/main.cpp
    src/external/glad/glad.c
    src/utility/file/FileUtility.cpp
)

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
