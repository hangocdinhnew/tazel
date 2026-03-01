#pragma once

#include <memory>
#include <optional>

#include "Tazel/Base/Window.hpp"
#include "Tazel/Renderer/RenderTexture.hpp"
#include "Tazel/Renderer/RendererFrame.hpp"

namespace Tazel {
  
  class Renderer {
  public:
    virtual ~Renderer() = default;
    
    virtual void Init() = 0;
    
    virtual std::unique_ptr<RenderTexture> CreateTexture(const TextureDesc& desc) = 0;
    virtual void DestroyTexture(RenderTexture& texture) = 0;
    
    virtual std::unique_ptr<RendererFrame> BeginFrame() = 0;
    virtual void EndFrame(RendererFrame& baseFrame) = 0;
    
    static std::unique_ptr<Renderer> Create(Window* Window);
  };
  
}
