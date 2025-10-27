#include "Tazel/Renderer/RendererAPI.hpp"
#include "Platform/SDL/SDLRenderer.hpp"

#include "Tazel/Renderer/Renderer.hpp"

namespace Tazel {

  static RendererAPI s_RAPI = GetRendererAPI(); 
  
  std::unique_ptr<Renderer> Renderer::Create(Window* Window)
  {
    switch (s_RAPI) {
    case RendererAPI::None: { TZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); } return nullptr;
    case RendererAPI::SDLGPU: return std::make_unique<SDLRenderer>(Window);
    }

    TZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

}
