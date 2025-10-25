#include "Tazel/Log.hpp"

#include "Platform/SDL/SDLWindow.hpp"

namespace Tazel {

  SDLWindow::SDLWindow(const WindowProps& props)
  {
    Init(props);
  }
  
  SDLWindow::~SDLWindow()
  {
    Shutdown();
  }
  
  void SDLWindow::Init(const WindowProps& props)
  {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    
    TZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
    
    m_Window = SDL_CreateWindow(m_Data.Title.c_str(), (int)props.Width, (int)props.Height, 0);
  }
  
  void SDLWindow::Shutdown()
  {
    SDL_DestroyWindow(m_Window);
  }
  
  void SDLWindow::OnUpdate(bool& isRunning)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
	isRunning = false;
	break;
      default:
	break;
      }
    }
  }
}
