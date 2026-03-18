#pragma once

#include "Tazel/Renderer/RendererAPI.hpp"
#include "Tazel/Renderer/RendererFrame.hpp"
#include "Tazel/Renderer/RenderPass.hpp"

namespace Tazel {
  class Renderer {
  public:
    Renderer() = default;
    ~Renderer() = default;

    void Init(Window* window);

    void Begin();
    void End();

    void SetClearColor(glm::vec4 ClearColor) { m_ClearColor = ClearColor; }

  private:
    glm::vec4 m_ClearColor = {0.0f,0.0f,0.0f,1.0f};
    
    std::unique_ptr<RendererAPI> m_RendererAPI;

    std::unique_ptr<RendererFrame> m_CurrentFrame;
    std::vector<std::unique_ptr<RenderPass>> m_RenderPasses;
  };
}
