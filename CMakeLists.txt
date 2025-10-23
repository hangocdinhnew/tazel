cmake_minimum_required(VERSION 3.20)

project(Tazel LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Deps
add_subdirectory(Libraries/spdlog)

add_subdirectory(tazel)
add_subdirectory(sandbox)
