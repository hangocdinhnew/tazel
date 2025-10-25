#pragma once

#include <memory>

#include "Tazel/Events/Event.hpp"
#include "Tazel/Window.hpp"

namespace Tazel {
  class Application {
  public:
    Application();
    ~Application();

    void Run();

  private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
  };

  Application* CreateApplication();
}
