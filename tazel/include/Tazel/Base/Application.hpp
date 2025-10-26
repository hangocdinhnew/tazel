#pragma once

#include <memory>

#include "Tazel/Events/ApplicationEvent.hpp"
#include "Tazel/Base/Window.hpp"
#include "Tazel/Renderer/GraphicsInstance.hpp"
#include "Tazel/Layers/LayerStack.hpp"

namespace Tazel {
  class Application {
  public:
    Application();
    ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

  private:
    bool OnWindowClose(WindowCloseEvent& e);
    
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<GraphicsInstance> m_GraphicsInstance;
    
    bool m_Running = true;
    LayerStack m_LayerStack;
  };

  Application* CreateApplication();
}
