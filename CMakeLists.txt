cmake_minimum_required(VERSION 3.20)

project(Tazel LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (MSVC)
  message(FATAL_ERROR "MSVC is no longer supported! Use MSYS2 (Specifically MINGW)!")
endif()

# Deps
find_package(spdlog CONFIG REQUIRED)

pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)

find_package(glm CONFIG REQUIRED)

macro(tazel_files_append)
  file(GLOB_RECURSE FILES_APPEND CONFIGURE_DEPENDS ${ARGV})
  list(APPEND ${ARGV0} ${FILES_APPEND})
endmacro()

macro(tazel_sources_append)
  tazel_files_append(${ARGV0} ${ARGV1}/*.h)
  tazel_files_append(${ARGV0} ${ARGV1}/*.hpp)
  tazel_files_append(${ARGV0} ${ARGV1}/*.c)
  tazel_files_append(${ARGV0} ${ARGV1}/*.cpp)
endmacro()

add_subdirectory(tazel)
add_subdirectory(sandbox)
