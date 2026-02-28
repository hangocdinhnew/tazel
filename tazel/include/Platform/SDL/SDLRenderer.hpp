#pragma once

#include "Tazel/Renderer/Renderer.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {

  class SDLTexture : public RenderTexture {
  public:
    SDL_GPUTexture* Texture = nullptr;
  };

  class SDLPass : public RenderPass {
  public:
    SDL_GPURenderPass* render_pass;
  };

  class SDLFrame : public RendererFrame {
  public:
    SDL_GPUCommandBuffer* CmdBuf = nullptr;
    SDL_GPUTexture* BackBuffer = nullptr;

    std::unique_ptr<RenderPass> BeginRenderPass(const RenderPassDesc& desc) override;
    void EndRenderPass(RenderPass& pass) override;
  };

  class SDLRenderer : public Renderer {
  public:
    SDLRenderer(Window* Window);
    virtual ~SDLRenderer() = default;

    void Init() override;

    std::unique_ptr<RenderTexture> CreateTexture(const TextureDesc& desc) override;
    void DestroyTexture(RenderTexture& texture) override;

    std::unique_ptr<RendererFrame> BeginFrame() override;
    void EndFrame(RendererFrame& baseFrame) override;

  private:
    unsigned int w = 0;
    unsigned int h = 0;
    
    Window* m_WindowHandle;
    SDLWindow* m_SDLWindow;
    
    std::unique_ptr<SDLInstance> m_Instance;
  };
  
}
