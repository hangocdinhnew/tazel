#include "Platform/SDL/SDLTexture.hpp"

namespace Tazel {
  SDLTexture::~SDLTexture() {
    SDL_ReleaseGPUTexture(Device, Texture);
  }
}
