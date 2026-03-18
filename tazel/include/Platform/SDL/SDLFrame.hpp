#pragma once

#include "Tazel/Renderer/RendererFrame.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {

  class SDLFrame : public RendererFrame {
  public:
    ~SDLFrame() override;
    
    SDL_GPUCommandBuffer* CmdBuf = nullptr;
    SDL_GPUTexture* BackBuffer = nullptr;

    std::unique_ptr<RenderPass> BeginRenderPass(const RenderPassDesc& desc) override;
  };

};
