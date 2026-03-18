#pragma once

#include <memory>
#include <optional>

#include "Tazel/Base/Window.hpp"
#include "Tazel/Renderer/RenderTexture.hpp"
#include "Tazel/Renderer/RendererFrame.hpp"

namespace Tazel {
  
  class RendererAPI {
  public:
    virtual ~RendererAPI() = default;
    
    virtual void Init() = 0;
    
    virtual std::unique_ptr<RenderTexture> CreateTexture(const TextureDesc& desc) = 0;
    
    virtual std::unique_ptr<RendererFrame> BeginFrame() = 0;
    
    static std::unique_ptr<RendererAPI> Create(Window* Window);
  };
  
}
