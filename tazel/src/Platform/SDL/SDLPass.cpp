#include "Platform/SDL/SDLPass.hpp"
#include "Tazel/Base/Log.hpp"

namespace Tazel {

  SDLPipeline::~SDLPipeline() {
    SDL_ReleaseGPUGraphicsPipeline(device, pipeline);
  }

  SDLBuffer::~SDLBuffer() {
    SDL_ReleaseGPUBuffer(device, buffer);
  }

  void SDLPass::BindPipeline(Pipeline& pipeline) {
    auto sdl_pipeline = static_cast<SDLPipeline&>(pipeline);

    SDL_BindGPUGraphicsPipeline(render_pass, sdl_pipeline.pipeline);
  }

  void SDLPass::BindVertexBuffer(Buffer& buffer) {
    auto sdl_buffer = static_cast<SDLBuffer&>(buffer);

    TZ_CORE_INFO("Buffer typeid: {}", typeid(buffer).name());
    TZ_CORE_INFO("SDL Buffer: {:p}", (void*)sdl_buffer.buffer);
    TZ_CORE_INFO("RenderPass ptr: {:p}", (void*)render_pass);

    SDL_GPUBufferBinding bufferBinding{};
    bufferBinding.buffer = sdl_buffer.buffer;
    bufferBinding.offset = 0;

    SDL_BindGPUVertexBuffers(render_pass, 0, &bufferBinding, 1);
  }

  void SDLPass::BindIndexBuffer(Buffer& buffer) {
    auto sdl_buffer = static_cast<SDLBuffer&>(buffer);

    SDL_GPUBufferBinding bufferBinding{};
    bufferBinding.buffer = sdl_buffer.buffer;
    bufferBinding.offset = 0;
    SDL_BindGPUIndexBuffer(render_pass, &bufferBinding, SDL_GPU_INDEXELEMENTSIZE_32BIT);
  }

  void SDLPass::DrawIndexed(uint32_t indexCount) {
    SDL_DrawGPUIndexedPrimitives(render_pass, indexCount, 1, 0, 0, 0);
  }

}
