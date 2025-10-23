#pragma once

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
