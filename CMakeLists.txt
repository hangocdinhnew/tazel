cmake_minimum_required(VERSION 3.20)

project(Tazel LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (MSVC)
  message(FATAL_ERROR "MSVC is no longer supported! Use MSYS2 (Specifically MINGW)!")
endif()

# Deps
add_subdirectory(Libraries/spdlog)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(Libraries/SDL)

add_subdirectory(tazel)
add_subdirectory(sandbox)
