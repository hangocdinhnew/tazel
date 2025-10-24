#include "Tazel/Application.hpp"

#include "Tazel/Log.hpp"
#include "Tazel/Events/ApplicationEvent.hpp"

namespace Tazel {

  Application::Application() {}
  Application::~Application() {}

  void Application::Run() {
    WindowResizeEvent e(420, 420);
    TZ_TRACE("{}", e.ToString());
    
    while (true);
  }
  
}
