add_library(Tazel STATIC)

target_sources(Tazel
  PRIVATE
  src/Tazel/Log.cpp
  src/Platform/SDL/SDLWindow.cpp
  src/Tazel/Application.cpp

  src/Tazel/Layer.cpp
  src/Tazel/LayerStack.cpp

  PUBLIC
  include/Tazel/Log.hpp
  include/Tazel/Application.hpp
  include/Tazel/EntryPoint.hpp
  include/Tazel/Window.hpp

  include/Tazel/Layer.hpp
  include/Tazel/LayerStack.hpp

  include/Tazel/Events/Event.hpp
  include/Tazel/Events/KeyEvent.hpp
  include/Tazel/Events/MouseEvent.hpp
  include/Tazel/Events/ApplicationEvent.hpp

  include/Platform/SDL/SDLWindow.hpp
  
  include/Tazel.hpp
)

target_include_directories(Tazel
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Tazel PUBLIC SDL3::SDL3)
target_link_libraries(Tazel PUBLIC spdlog::spdlog)
