#pragma once

#include <memory>
#include <optional>

#include "Tazel/Base/Window.hpp"
#include "Tazel/Renderer/RenderTexture.hpp"
#include "Tazel/Renderer/RendererFrame.hpp"

namespace Tazel {

  struct Vertex {
    glm::vec3 Position;
    float padding;
    
    // glm::vec3 Normal;
    // glm::vec2 UV;
  };

  struct ShaderDesc {
    const uint8_t* data;
    size_t size;

    uint32_t numUniformBuffers = 0;
    uint32_t numSamplers = 0;
    uint32_t numStorageBuffers = 0;
    uint32_t numStorageTextures = 0;
  };

  enum class FillMode {
    Fill,
    Line
  };

  class RendererAPI {
  public:
    virtual ~RendererAPI() = default;
    
    virtual void Init() = 0;
    
    virtual std::unique_ptr<RenderTexture> CreateTexture(const TextureDesc& desc) = 0;
    virtual void DestroyTexture(RenderTexture& texture) = 0;
    
    virtual std::unique_ptr<RendererFrame> BeginFrame() = 0;
    virtual void EndFrame(RendererFrame& baseFrame) = 0;

    virtual std::shared_ptr<Pipeline> CreatePipeline(const ShaderDesc& vert, const ShaderDesc& frag, FillMode fillmode = FillMode::Fill) = 0;

    virtual std::shared_ptr<Buffer> CreateVertexBuffer(const void* data, size_t size) = 0;
    virtual std::shared_ptr<Buffer> CreateIndexBuffer(const void* data, size_t size) = 0;

    static std::unique_ptr<RendererAPI> Create(Window* Window);
  };
  
}
