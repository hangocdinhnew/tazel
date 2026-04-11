#pragma once

#include "Tazel/Renderer/RenderPass.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {

  class SDLPipeline : public Pipeline {
  public:
    ~SDLPipeline();
    
    SDL_GPUDevice* device;
    SDL_GPUGraphicsPipeline* pipeline;
  };

  class SDLBuffer : public Buffer {
  public:
    ~SDLBuffer();
    
    SDL_GPUDevice* device;
    SDL_GPUBuffer* buffer;
  };

  class SDLPass : public RenderPass {
  public:
    SDL_GPURenderPass* render_pass;

    void BindPipeline(Pipeline& pipeline) override;

    void BindVertexBuffer(Buffer& buffer) override;
    void BindIndexBuffer(Buffer& buffer) override;

    // void SetUniform(const std::string& name, const void* data, size_t size) override;
    // TODO: To be implemented

    void DrawIndexed(uint32_t indexCount) override;
  };

}
