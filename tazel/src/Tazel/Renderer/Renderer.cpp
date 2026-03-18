#include "Tazel/Base/Log.hpp"
#include "Tazel/Renderer/Renderer.hpp"

namespace Tazel {
  void Renderer::Init(Window* window) {
    m_RendererAPI = RendererAPI::Create(window);
    m_RendererAPI->Init();
  }

  void Renderer::Begin() {
    if (!m_CurrentFrame)
      m_CurrentFrame = m_RendererAPI->BeginFrame();

    RenderPassDesc desc;
    desc.colorAttachments.push_back({.clearValue = m_ClearColor});
    m_RenderPasses.push_back(m_CurrentFrame->BeginRenderPass(desc));
  }

  void Renderer::End() {
    TZ_CORE_ASSERT(m_CurrentFrame, "Renderer: Called End without Starting!");

    for (auto& pass : m_RenderPasses)
      m_CurrentFrame->EndRenderPass(*pass);
    m_RenderPasses.clear();

    m_RendererAPI->EndFrame(*m_CurrentFrame);

    m_CurrentFrame.reset();
  }
}
