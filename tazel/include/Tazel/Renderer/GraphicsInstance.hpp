#pragma once

#include <memory>

#include "Tazel/Base/Window.hpp"

namespace Tazel {
  
  class GraphicsInstance {
  public:
    virtual ~GraphicsInstance() = default;
    
    virtual void Init() = 0;
  };
  
}
