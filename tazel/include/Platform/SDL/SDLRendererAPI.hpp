#pragma once

#include "Tazel/Renderer/RendererAPI.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"
#include "Platform/SDL/SDLTexture.hpp"
#include "Platform/SDL/SDLFrame.hpp"

namespace Tazel {

  class SDLRendererAPI : public RendererAPI {
  public:
    SDLRendererAPI(Window* Window);
    virtual ~SDLRendererAPI() = default;

    void Init() override;

    std::unique_ptr<RenderTexture> CreateTexture(const TextureDesc& desc) override;

    std::unique_ptr<RendererFrame> BeginFrame() override;

  private:
    unsigned int w = 0;
    unsigned int h = 0;
    
    Window* m_WindowHandle;
    SDLWindow* m_SDLWindow;
    
    std::unique_ptr<SDLInstance> m_Instance;
  };
  
}
