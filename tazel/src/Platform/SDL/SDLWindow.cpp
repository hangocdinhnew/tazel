#include "Tazel/Base/Log.hpp"

#include "Tazel/Events/ApplicationEvent.hpp"
#include "Tazel/Events/MouseEvent.hpp"
#include "Tazel/Events/KeyEvent.hpp"

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
  
  void SDLWindow::OnUpdate()
  {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT: {
        WindowCloseEvent e;
        m_Data.EventCallback(e);
        break;
      }
	
      case SDL_EVENT_WINDOW_RESIZED: {
        WindowResizeEvent e(event.window.data1, event.window.data2);
        m_Data.Width = event.window.data1;
        m_Data.Height = event.window.data2;
        m_Data.EventCallback(e);
        break;
      }
	
      case SDL_EVENT_KEY_DOWN: {
        KeyPressedEvent e(event.key.scancode, event.key.key, 0);
        m_Data.EventCallback(e);
        break;
      }
	
      case SDL_EVENT_KEY_UP: {
        KeyReleasedEvent e(event.key.scancode, event.key.key);
        m_Data.EventCallback(e);
        break;
      }
	
      case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        MouseButtonPressedEvent e(event.button.button);
        m_Data.EventCallback(e);
        break;
      }
	
      case SDL_EVENT_MOUSE_BUTTON_UP: {
        MouseButtonReleasedEvent e(event.button.button);
        m_Data.EventCallback(e);
        break;
      }
	
      case SDL_EVENT_MOUSE_MOTION: {
        MouseMovedEvent e((float)event.motion.x, (float)event.motion.y);
        m_Data.EventCallback(e);
        break;
      }
	
      case SDL_EVENT_MOUSE_WHEEL: {
        MouseScrolledEvent e((float)event.wheel.x, (float)event.wheel.y);
        m_Data.EventCallback(e);
        break;
      }
      }
    }
  }
}
