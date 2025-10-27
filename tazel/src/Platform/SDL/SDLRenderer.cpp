#include "Tazel/Base/Log.hpp"

#include "Platform/SDL/SDLRenderer.hpp"

namespace Tazel {

  SDLRenderer::SDLRenderer(Window* Window) : m_WindowHandle(Window)
  {
    TZ_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
  }

  void SDLRenderer::Init()
  {
    m_Instance = std::make_unique<SDLInstance>(m_WindowHandle);

    m_SDLWindow = dynamic_cast<SDLWindow*>(m_WindowHandle);
    TZ_CORE_ASSERT(m_SDLWindow, "Failed to get SDL Window!");
  }

  void SDLRenderer::Acquire()
  {
    TZ_CORE_INFO("Testing::Acquire");
    
    m_CmdBuf = SDL_AcquireGPUCommandBuffer(m_Instance->GetGPUDevice());
    TZ_CORE_ASSERT(m_CmdBuf, "Failed to acquire Command Buffer! Reason: {}", SDL_GetError());

    if (!SDL_WaitAndAcquireGPUSwapchainTexture(m_CmdBuf, m_SDLWindow->GetWindow(), &m_SCTexture, NULL, NULL))
      TZ_CORE_ASSERT(false, "Failed to wait and acquire Swapchain texture! Reason: {}", SDL_GetError());
  }

  void SDLRenderer::Swapbuffers()
  {
    TZ_CORE_INFO("Testing::Swapbuffers");
    
    SDL_SubmitGPUCommandBuffer(m_CmdBuf);
  }

  void SDLRenderer::ClearColor(const glm::vec4& color)
  {
    TZ_CORE_INFO("Testing::ClearColor");
    
    SDL_GPUColorTargetInfo colorTargetInfo{};
    colorTargetInfo.texture = m_SCTexture;
    colorTargetInfo.clear_color = (SDL_FColor) { color.r, color.g, color.b, color.a };
    colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

    SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(m_CmdBuf, &colorTargetInfo, 1, NULL);
    SDL_EndGPURenderPass(renderPass);
  }
  
}
