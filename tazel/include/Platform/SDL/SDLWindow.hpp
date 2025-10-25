#pragma once

#include "Tazel/Window.hpp"

#include <SDL3/SDL.h>

namespace Tazel {
  
  class SDLWindow : public Window
  {
  public:
    SDLWindow(const WindowProps& props);
    virtual ~SDLWindow();
    
    void OnUpdate(bool& isRunning) override;
    
    inline unsigned int GetWidth() const override { return m_Data.Width; }
    inline unsigned int GetHeight() const override { return m_Data.Height; }
    
    inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

  private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

  private:
    SDL_Window* m_Window;
    
    struct WindowData
    {
      std::string Title;
      unsigned int Width, Height;
      EventCallbackFn EventCallback;
    };
    
    WindowData m_Data;
  };

}
