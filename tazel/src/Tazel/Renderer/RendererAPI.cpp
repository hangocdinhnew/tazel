#include "Tazel/Base/Log.hpp"
#include "Platform/SDL/SDLRendererAPI.hpp"

#include "Tazel/Renderer/RendererAPI.hpp"

enum class RendererEnum {
  None = 0,
  SDLGPU,
};

static RendererEnum GetRendererEnum() {
  return RendererEnum::SDLGPU;
}

namespace Tazel {

  static RendererEnum s_RAPI = GetRendererEnum(); 
  
  std::unique_ptr<RendererAPI> RendererAPI::Create(Window* Window) {
    switch (s_RAPI) {
    case RendererEnum::None: { TZ_CORE_ASSERT(false, "RendererEnum::None is currently not supported"); } return nullptr;
    case RendererEnum::SDLGPU: return std::make_unique<SDLRendererAPI>(Window);
    }

    TZ_CORE_ASSERT(false, "Unknown RendererEnum!");
    return nullptr;
  }

}
