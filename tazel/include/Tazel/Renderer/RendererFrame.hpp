#pragma once

#include "Tazel/Renderer/RenderPass.hpp"

namespace Tazel {
  class RendererFrame {
  public:
    virtual ~RendererFrame() = default;
    
    virtual std::unique_ptr<RenderPass> BeginRenderPass(const RenderPassDesc& desc) = 0;
  };
};
