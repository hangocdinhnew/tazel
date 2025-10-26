#include "Tazel/Base/Base.h"
#include "Tazel/Base/Log.hpp"
#include "Platform/SDL/SDLWindow.hpp"

#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {

  SDLInstance::SDLInstance(Window* Window) : m_WindowHandle(Window)
  {
    TZ_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
  }

  SDLInstance::~SDLInstance()
  {
    TZ_CORE_ASSERT(m_GPUDevice, "GPU device not created yet!");
    Shutdown();
  }

  void SDLInstance::Init() {
    m_GPUDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, "vulkan");
    TZ_CORE_ASSERT(m_GPUDevice, "Failed to create GPU Device!");

    auto sdlwindow = dynamic_cast<SDLWindow*>(m_WindowHandle);
    m_Window = sdlwindow->GetWindow();

    if(!SDL_ClaimWindowForGPUDevice(m_GPUDevice, m_Window))
      TZ_CORE_ASSERT(false, "Failed to claim Window for GPU device!");
  }

  void SDLInstance::Shutdown() {
    SDL_ReleaseWindowFromGPUDevice(m_GPUDevice, m_Window);
    SDL_DestroyGPUDevice(m_GPUDevice);
  }
  
}
