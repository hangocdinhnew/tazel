#pragma once

#include <memory>

#include "Tazel/Events/ApplicationEvent.hpp"
#include "Tazel/Window.hpp"

namespace Tazel {
  class Application {
  public:
    Application();
    ~Application();

    void Run();

    void OnEvent(Event& e);

  private:
    bool OnWindowClose(WindowCloseEvent& e);
    
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
  };

  Application* CreateApplication();
}
