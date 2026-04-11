#include "Tazel/Base/Log.hpp"
#include "Tazel/Renderer/Renderer.hpp"
#include BASIC_VERT
#include BASIC_FRAG

namespace Tazel {

  void Renderer::Upload(Mesh* mesh) {
    auto vertexBuffer = m_RendererAPI->CreateVertexBuffer(mesh->Vertices.data(),
					     mesh->Vertices.size() * sizeof(Vertex));
    mesh->SetVertexBuffer(vertexBuffer);

    auto indexBuffer = m_RendererAPI->CreateIndexBuffer(mesh->Indices.data(),
					   mesh->Indices.size() * sizeof(uint32_t));
    mesh->SetIndexBuffer(indexBuffer);

    mesh->SetIndexCount(static_cast<uint32_t>(mesh->Indices.size()));
  }
  
  void Renderer::Init(Window* window) {
    m_RendererAPI = RendererAPI::Create(window);
    m_RendererAPI->Init();

    m_DefaultPipeline = m_RendererAPI->CreatePipeline({ Basic_vert, Basic_vert_len}, { Basic_frag, Basic_frag_len });
    m_WireframePipeline = m_RendererAPI->CreatePipeline({ Basic_vert, Basic_vert_len}, { Basic_frag, Basic_frag_len }, FillMode::Line);
  }

  void Renderer::Begin() {
    m_CurrentFrame = m_RendererAPI->BeginFrame();
  }

  // TODO: To be implemented
  // void Renderer::Submit(Mesh* mesh, Material* material, const glm::mat4& transform) {
  //   m_DrawQueue.push_back({ mesh, material, transform });
  // }

  void Renderer::Submit(Mesh* mesh) {
    m_DrawQueue.push_back({ mesh });
  }

  void Renderer::End() {
    TZ_CORE_INFO("Called!");
    
    TZ_CORE_ASSERT(m_CurrentFrame, "Renderer: Called End without Starting!");

    RenderPassDesc desc{};
    desc.colorAttachments.push_back({ .clearValue = m_ClearColor });

    auto pass = m_CurrentFrame->BeginRenderPass(desc);
    pass->BindPipeline(useWireFrame ? *m_WireframePipeline : *m_DefaultPipeline);
    
    for (auto& cmd : m_DrawQueue) {
      // cmd.material->Bind(pass.get());
      // TODO: TO be implemented

      // pass->SetUniform("u_Model", &cmd.transform, sizeof(glm::mat4));
      // TODO: To be implemented

      cmd.mesh->Bind(*pass);
      cmd.mesh->Draw(*pass);
    }

    m_CurrentFrame->EndRenderPass(*pass);

    m_RendererAPI->EndFrame(*m_CurrentFrame);

    m_DrawQueue.clear();
    m_CurrentFrame.reset();
  }
}
