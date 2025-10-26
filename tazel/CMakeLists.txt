add_library(Tazel STATIC)

target_sources(Tazel
  PRIVATE
  src/Tazel/Base/Log.cpp
  src/Tazel/Base/Application.cpp

  src/Platform/SDL/SDLWindow.cpp

  src/Tazel/Layers/Layer.cpp
  src/Tazel/Layers/LayerStack.cpp

  PUBLIC
  include/Tazel/Base/Log.hpp
  include/Tazel/Base/Application.hpp
  include/Tazel/Base/EntryPoint.hpp
  include/Tazel/Base/Window.hpp

  include/Tazel/Layers/Layer.hpp
  include/Tazel/Layers/LayerStack.hpp

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
