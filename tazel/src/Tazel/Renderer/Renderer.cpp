#include "Tazel/Base/Log.hpp"
#include "Platform/SDL/SDLRenderer.hpp"

#include "Tazel/Renderer/Renderer.hpp"

enum class RendererAPI {
  None = 0,
  SDLGPU,
};

static RendererAPI GetRendererAPI() {
  return RendererAPI::SDLGPU;
}

namespace Tazel {

  static RendererAPI s_RAPI = GetRendererAPI(); 
  
  std::unique_ptr<Renderer> Renderer::Create(Window* Window) {
    switch (s_RAPI) {
    case RendererAPI::None: { TZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); } return nullptr;
    case RendererAPI::SDLGPU: return std::make_unique<SDLRenderer>(Window);
    }

    TZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

}
