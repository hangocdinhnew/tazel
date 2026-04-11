#pragma once

#include <glm/glm.hpp>

#include "Tazel/Renderer/RenderTexture.hpp"

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
    RenderTexture* texture = nullptr;
    
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

  class Pipeline {
  public:
    virtual ~Pipeline() = default;
  };

  class Buffer {
  public:
    virtual ~Buffer() = default;
  };

  class RenderPass {
  public:
    virtual ~RenderPass() = default;

    virtual void BindPipeline(Pipeline& pipeline) = 0;

    virtual void BindVertexBuffer(Buffer& buffer) = 0;
    virtual void BindIndexBuffer(Buffer& buffer) = 0;

    // virtual void SetUniform(const std::string& name, const void* data, size_t size) = 0;
    // TODO: To be implemented

    virtual void DrawIndexed(uint32_t indexCount) = 0;
  };

};
  
