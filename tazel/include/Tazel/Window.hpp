#pragma once

#include "Tazel/Events/Event.hpp"

namespace Tazel {
  
  struct WindowProps
  {
    std::string Title;
    unsigned int Width;
    unsigned int Height;
    
    WindowProps(const std::string& title = "Tazel Engine",
		unsigned int width = 1280,
		unsigned int height = 720)
      : Title(title), Width(width), Height(height)
    {
    }
  };
  
  class Window
  {
  public:
    using EventCallbackFn = std::function<void(Event&)>;
    
    virtual ~Window() {}
    
    virtual void OnUpdate(bool& isRunning) = 0;
    
    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;
    
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
  };
  
}
