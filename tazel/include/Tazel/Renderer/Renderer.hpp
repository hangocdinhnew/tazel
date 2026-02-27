#pragma once

#include <memory>
#include <optional>

#include <glm/glm.hpp>

#include "Tazel/Base/Window.hpp"

namespace Tazel {
  
  enum class LoadOp {
    Load,
    Clear,
    DontCare
  };
  
  enum class StoreOp {
    Store,
    DontCare
  };

  struct ColorAttachmentDesc {
    LoadOp loadOp = LoadOp::Clear;
    StoreOp storeOp = StoreOp::Store;
    
    glm::vec4 clearValue = {0, 0, 0, 1};
  };

  struct DepthStencilAttachmentDesc {
    LoadOp depthLoadOp = LoadOp::Load;
    StoreOp depthStoreOp = StoreOp::DontCare;
    
    LoadOp stencilLoadOp = LoadOp::DontCare;
    StoreOp stencilStoreOp = StoreOp::DontCare;
    
    float clearDepth = 1.0f;
    uint8_t clearStencil = 0;
  };

  struct RenderPassDesc {
    std::vector<ColorAttachmentDesc> colorAttachments;
    std::optional<DepthStencilAttachmentDesc> depthStencilAttachment = std::nullopt;
  };

  class RenderPass {
  public:
    virtual ~RenderPass() = default;
  };

  class RendererFrame {
  public:
    virtual ~RendererFrame() = default;

    virtual std::unique_ptr<RenderPass> BeginRenderPass(const RenderPassDesc& desc) = 0;
    virtual void EndRenderPass(RenderPass& pass) = 0;
  };

  class Renderer {
  public:
    virtual ~Renderer() = default;

    virtual void Init() = 0;

    virtual std::unique_ptr<RendererFrame> BeginFrame() = 0;
    virtual void EndFrame(RendererFrame& baseFrame) = 0;
    
    static std::unique_ptr<Renderer> Create(Window* Window);
  };
  
}
