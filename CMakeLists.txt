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

if(APPLE)
  find_program(HOMEBREW_EXECUTABLE brew)

  if(HOMEBREW_EXECUTABLE)
    execute_process(
      COMMAND "${HOMEBREW_EXECUTABLE}" --prefix openal-soft
      OUTPUT_VARIABLE OPENAL_SOFT_PREFIX
      OUTPUT_STRIP_TRAILING_WHITESPACE
      RESULT_VARIABLE OPENAL_SOFT_RESULT)

    if(OPENAL_SOFT_RESULT EQUAL 0)
      list(PREPEND CMAKE_PREFIX_PATH "${OPENAL_SOFT_PREFIX}")
    endif()
  endif()
endif()

find_package(PkgConfig REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 3.3 REQUIRED)

pkg_check_modules(
  OPENAL
  REQUIRED
  IMPORTED_TARGET
  openal)

pkg_check_modules(
  SNDFILE
  REQUIRED
  IMPORTED_TARGET
  sndfile)

add_executable(ducky-jam ${DUCKY_JAM_SOURCES})

target_compile_definitions(ducky-jam PRIVATE GLFW_INCLUDE_NONE)

target_include_directories(ducky-jam PRIVATE ${OPENAL_INCLUDE_DIRS} ${SNDFILE_INCLUDE_DIRS}
                                             ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(
  ducky-jam
  PRIVATE PkgConfig::OPENAL
          PkgConfig::SNDFILE
          glfw
          fmt::fmt)

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

target_link_options(ducky-jam PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)

target_compile_options(
  ducky-jam
  PRIVATE $<$<CONFIG:Release>:-O3
          -march=native
          -ffunction-sections
          -fdata-sections>)

target_compile_options(
  ducky-jam
  PRIVATE $<$<CONFIG:Debug>:-O1
          -g
          -fsanitize=address
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
