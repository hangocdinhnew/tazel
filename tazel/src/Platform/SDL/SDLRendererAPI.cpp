#include <cassert>

#include "Tazel/Base/Log.hpp"

#include "Platform/SDL/SDLRendererAPI.hpp"

namespace Tazel {

  SDLRendererAPI::SDLRendererAPI(Window* Window) : m_WindowHandle(Window) {
    TZ_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
  }
  
  void SDLRendererAPI::Init() {
    m_Instance = std::make_unique<SDLInstance>(m_WindowHandle);
    m_Instance->Init();
    
    m_SDLWindow = static_cast<SDLWindow*>(m_WindowHandle);
    TZ_CORE_ASSERT(m_SDLWindow, "Failed to get SDL Window!");
  }
  
  std::unique_ptr<RendererFrame> SDLRendererAPI::BeginFrame() {
    auto frame = std::make_unique<SDLFrame>();
    
    frame->CmdBuf = SDL_AcquireGPUCommandBuffer(m_Instance->GetGPUDevice());
    TZ_CORE_ASSERT(frame->CmdBuf, "Failed to acquire Command Buffer! Reason: '{}'", SDL_GetError());
    
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(frame->CmdBuf, m_SDLWindow->GetWindow(), &frame->BackBuffer, &w, &h))
      TZ_CORE_ASSERT(false, "Failed to wait and acquire Swapchain texture! Reason: '{}'", SDL_GetError());
    
    return frame;
  }
  
  void SDLRendererAPI::EndFrame(RendererFrame& baseFrame) {
    auto& sdlFrame = static_cast<SDLFrame&>(baseFrame);
    
    SDL_SubmitGPUCommandBuffer(sdlFrame.CmdBuf);
  }

  std::unique_ptr<RenderTexture> SDLRendererAPI::CreateTexture(const TextureDesc& desc) {
    auto sdlTexture = std::make_unique<SDLTexture>();

    auto format = desc.format;
    
    if (format == TextureFormat::Invalid)
      format = static_cast<TextureFormat>(SDL_GetGPUSwapchainTextureFormat(m_Instance->GetGPUDevice(), m_SDLWindow->GetWindow()));

    unsigned int nw = desc.width;
    unsigned int nh = desc.height;

    if (nw == 0 || nh == 0) {
      TZ_CORE_ASSERT(w != 0 && h != 0, "Width and height of swapchain texture is zero! Make sure you have called CreateTexture **AFTER** BeginFrame");
      
      nw = w;
      nh = h;
    }
      
    const SDL_GPUTextureCreateInfo createInfo = {
      .type = static_cast<SDL_GPUTextureType>(desc.type),
      .format = static_cast<SDL_GPUTextureFormat>(format),
      .usage = static_cast<SDL_GPUTextureUsageFlags>(desc.usage),

      .width = nw,
      .height = nh,

      .sample_count = static_cast<SDL_GPUSampleCount>(desc.sample)
    };

    sdlTexture->Texture = SDL_CreateGPUTexture(m_Instance->GetGPUDevice(), &createInfo);

    return sdlTexture;
  }

  void SDLRendererAPI::DestroyTexture(RenderTexture& texture) {
    auto& sdlTexture = static_cast<SDLTexture&>(texture);
    
    SDL_ReleaseGPUTexture(m_Instance->GetGPUDevice(), sdlTexture.Texture);
  }
  
}
