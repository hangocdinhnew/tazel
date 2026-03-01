#include "Tazel/Base/Log.hpp"
#include "Platform/SDL/SDLRenderer.hpp"

#include "Tazel/Renderer/Renderer.hpp"

enum class RendererEnum {
  None = 0,
  SDLGPU,
};

static RendererEnum GetRendererEnum() {
  return RendererEnum::SDLGPU;
}

namespace Tazel {

  static RendererEnum s_RAPI = GetRendererEnum(); 
  
  std::unique_ptr<Renderer> Renderer::Create(Window* Window) {
    switch (s_RAPI) {
    case RendererEnum::None: { TZ_CORE_ASSERT(false, "RendererEnum::None is currently not supported"); } return nullptr;
    case RendererEnum::SDLGPU: return std::make_unique<SDLRenderer>(Window);
    }

    TZ_CORE_ASSERT(false, "Unknown RendererEnum!");
    return nullptr;
  }

}
