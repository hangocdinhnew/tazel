#pragma once

#include "Tazel/Renderer/RendererFrame.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {

  class SDLFrame : public RendererFrame {
  public:
    SDL_GPUCommandBuffer* CmdBuf = nullptr;
    SDL_GPUTexture* BackBuffer = nullptr;

    std::unique_ptr<RenderPass> BeginRenderPass(const RenderPassDesc& desc) override;
    void EndRenderPass(RenderPass& pass) override;
  };

};
