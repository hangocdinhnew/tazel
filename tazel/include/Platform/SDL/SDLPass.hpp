#pragma once

#include "Tazel/Renderer/RenderPass.hpp"
#include "Platform/SDL/SDLWindow.hpp"
#include "Platform/SDL/SDLInstance.hpp"

namespace Tazel {

  class SDLPass : public RenderPass {
  public:
    ~SDLPass() override;
    
    SDL_GPURenderPass* render_pass;
  };

}
