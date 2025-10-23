add_executable(Sandbox)

target_sources(Sandbox
  PRIVATE
  src/SandboxApp.cpp

  PUBLIC
)

target_include_directories(Sandbox
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Sandbox PUBLIC Tazel)

if (NOT MSVC)
  target_link_libraries(Sandbox -static)
endif()
