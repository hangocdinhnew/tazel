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

target_link_libraries(Sandbox PRIVATE Tazel)

if (MINGW)
  target_link_libraries(Sandbox PRIVATE -static)
endif()
