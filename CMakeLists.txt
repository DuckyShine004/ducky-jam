cmake_minimum_required(VERSION 3.10)
project(
  ducky-jam
  VERSION 0.0.1
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

file(
  GLOB_RECURSE
  DUCKY_JAM_SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/*.c")

find_package(OpenAL CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
find_package(
  glfw3
  3.3
  CONFIG
  REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libzip CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(SqliteOrm CONFIG REQUIRED)

add_executable(ducky-jam ${DUCKY_JAM_SOURCES})

target_compile_definitions(ducky-jam PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(ducky-jam PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(
  ducky-jam
  PRIVATE OpenAL::OpenAL
          SndFile::sndfile
          glfw
          fmt::fmt
          nlohmann_json::nlohmann_json
          libzip::zip
          OpenSSL::Crypto
          sqlite_orm::sqlite_orm)

if(APPLE)
  target_link_options(
    ducky-jam
    PRIVATE
    $<$<CONFIG:Release>:-Wl,-dead_strip>
    $<$<CONFIG:Profile>:-Wl,-dead_strip>)
else()
  target_link_options(
    ducky-jam
    PRIVATE
    $<$<CONFIG:Release>:-Wl,--as-needed
    -Wl,--gc-sections>
    $<$<CONFIG:Profile>:-Wl,--as-needed>)
endif()

# target_link_options(ducky-jam PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
# target_link_options(ducky-jam PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)

target_compile_options(
  ducky-jam
  PRIVATE $<$<CONFIG:Release>:-O3
          -march=native
          -ffunction-sections
          -fdata-sections>)

target_compile_options(
  ducky-jam
  PRIVATE $<$<CONFIG:Debug>:-O1
          -g3
          # -fsanitize=address
          -fno-omit-frame-pointer
          -Wodr>)

target_compile_options(
  ducky-jam
  PRIVATE $<$<CONFIG:Profile>:-O2
          -g
          -fno-omit-frame-pointer
          -march=native>)

set_property(TARGET ducky-jam PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
set_property(TARGET ducky-jam PROPERTY INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE)
set_property(TARGET ducky-jam PROPERTY INTERPROCEDURAL_OPTIMIZATION_PROFILE FALSE)
