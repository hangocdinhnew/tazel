#include "Tazel/Base/Log.hpp"
#include "Tazel/Base/Application.hpp"

#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLRenderer.hpp"

namespace Tazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  Application::Application()
  {
    m_Window = std::make_unique<SDLWindow>(WindowProps());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    m_Renderer = Renderer::Create(m_Window.get());
    m_Renderer->Init();
  }
  
  Application::~Application() {}

  void Application::Run()
  {
    while (m_Running) {
      for (Layer* layer : m_LayerStack)
	layer->OnUpdate();
      
      m_Window->OnUpdate();

      m_Renderer->Acquire();
      m_Renderer->ClearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
      m_Renderer->Swapbuffers();
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
  }
  
  void Application::PushOverlay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
	(*--it)->OnEvent(e);

	if (e.Handled)
	  break;
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }
  
}
