#include "Platform/SDL/SDLPass.hpp"

namespace Tazel {
  SDLPass::~SDLPass() {
    SDL_EndGPURenderPass(render_pass);
  }
}
