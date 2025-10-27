#pragma once

#include <glm/glm.hpp>

#include "Tazel/Base/Window.hpp"

namespace Tazel {

  class Renderer {
  public:
    virtual ~Renderer() = default;

    virtual void Init() = 0;

    virtual void Acquire() = 0;
    virtual void ClearColor(const glm::vec4& color) = 0;
    virtual void Swapbuffers() = 0;
    
    static std::unique_ptr<Renderer> Create(Window* Window);
  };
  
}
