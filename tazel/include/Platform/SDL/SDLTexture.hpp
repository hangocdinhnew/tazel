#pragma once

#include "Tazel/Renderer/RendererFrame.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {
  class SDLTexture : public RenderTexture {
  public:
    SDL_GPUTexture* Texture = nullptr;
  };
}
