#include "Tazel/Application.hpp"

#include "Tazel/Log.hpp"

#include "Platform/SDL/SDLWindow.hpp"

namespace Tazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  Application::Application()
  {
    m_Window = std::make_unique<SDLWindow>(WindowProps());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
  }
  
  Application::~Application() {}

  void Application::Run() {
    while (m_Running) {
      m_Window->OnUpdate();
    }
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    TZ_CORE_TRACE("{0}", e.ToString());
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }
  
}
