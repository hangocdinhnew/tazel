#pragma once

#include "Tazel/Base/Window.hpp"

namespace Tazel {
  
  class GraphicsInstance {
  public:
    virtual ~GraphicsInstance() = default;
    
    virtual void Init() = 0;

    static std::unique_ptr<GraphicsInstance> Create(Window* Window);
  };
  
}
