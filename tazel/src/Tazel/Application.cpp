#include "Tazel/Application.hpp"

#include "Tazel/Log.hpp"
#include "Tazel/Events/ApplicationEvent.hpp"

#include "Platform/SDL/SDLWindow.hpp"

namespace Tazel {

  Application::Application() {
    m_Window = std::make_unique<SDLWindow>(WindowProps());
  }
  
  Application::~Application() {}

  void Application::Run() {
    while (m_Running) {
      m_Window->OnUpdate(m_Running);
    }
  }
  
}
