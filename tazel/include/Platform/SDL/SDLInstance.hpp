#pragma once

#include <SDL3/SDL.h>

#include "Tazel/Base/Window.hpp"
#include "Tazel/Renderer/GraphicsInstance.hpp"

namespace Tazel {
  
  class SDLInstance : public GraphicsInstance {
  public:
    SDLInstance(Window* Window);
    virtual ~SDLInstance();
    
    void Init() override;
    void Shutdown();

    SDL_GPUDevice* getGPUDevice() { return m_GPUDevice; }

  private:
    Window* m_WindowHandle;

    SDL_Window* m_Window;
    SDL_GPUDevice* m_GPUDevice;
  };
  
}
