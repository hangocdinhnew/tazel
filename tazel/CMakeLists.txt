add_library(Tazel STATIC)

target_sources(Tazel
  PRIVATE
  src/Tazel/Application.cpp

  PUBLIC
  include/Tazel/Application.hpp
  include/Tazel/EntryPoint.hpp
  include/Tazel.hpp
)

target_include_directories(Tazel
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Tazel PUBLIC spdlog::spdlog)
