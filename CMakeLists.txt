cmake_minimum_required(VERSION 3.10)
project(ducky_jam VERSION 0.0.1)

add_executable(ducky_jam
    src/main.cpp
    src/external/glad/glad.c
    src/engine/shader/Shader.cpp
    src/engine/shape/Shape.cpp
    src/engine/shape/rectangle/Rectangle.cpp
    src/engine/scene/Scene.cpp
    src/engine/mesh/Mesh.cpp
    src/component/Component.cpp
    src/component/game/singleplayer/play/area/Area.cpp
    src/component/game/singleplayer/play/area/Lane.cpp
    src/component/game/singleplayer/play/area/Note.cpp
    src/manager/SceneManager.cpp
    src/application/game/singleplayer/play/Play.cpp
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
