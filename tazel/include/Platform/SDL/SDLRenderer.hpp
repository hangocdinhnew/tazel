#pragma once

#include "Tazel/Renderer/Renderer.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {

  class SDLRenderer : public Renderer {
  public:
    SDLRenderer(Window* Window);
    virtual ~SDLRenderer() = default;

    void Init() override;

    void Acquire() override;
    void ClearColor(const glm::vec4& color) override;
    void Swapbuffers() override;

    SDL_GPUCommandBuffer* getCmdBuf() { return m_CmdBuf; }
    SDL_GPUTexture* getSCTexture() { return m_SCTexture; }

  private:
    Window* m_WindowHandle;
    SDLWindow* m_SDLWindow;
    
    std::unique_ptr<SDLInstance> m_Instance;
    
    SDL_GPUCommandBuffer* m_CmdBuf;
    SDL_GPUTexture* m_SCTexture;
  };
  
}
