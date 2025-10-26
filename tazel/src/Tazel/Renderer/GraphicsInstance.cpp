#include "Tazel/Renderer/RendererAPI.hpp"
#include "Platform/SDL/SDLInstance.hpp"

#include "Tazel/Renderer/GraphicsInstance.hpp"

namespace Tazel {

  static RendererAPI s_RAPI = GetRendererAPI(); 
  
  std::unique_ptr<GraphicsInstance> GraphicsInstance::Create(Window* Window) {
    switch (s_RAPI) {
    case RendererAPI::None: TZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
    case RendererAPI::SDLGPU: return std::make_unique<SDLInstance>(Window);
    }

    TZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}
