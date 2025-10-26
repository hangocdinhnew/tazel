#pragma once

#include <SDL3/SDL.h>

#include "Tazel/Base/Window.hpp"

namespace Tazel {
  
  class SDLWindow : public Window
  {
  public:
    SDLWindow(const WindowProps& props);
    virtual ~SDLWindow();
    
    void OnUpdate() override;
    
    inline unsigned int GetWidth() const override { return m_Data.Width; }
    inline unsigned int GetHeight() const override { return m_Data.Height; }
    
    inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

    SDL_Window* GetWindow() const { return m_Window; }

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
