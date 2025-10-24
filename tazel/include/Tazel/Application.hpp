#pragma once

#include "Tazel/Events/Event.hpp"

namespace Tazel {
  class Application {
  public:
    Application();
    ~Application();

    void Run();

  private:
  };

  Application* CreateApplication();
}
