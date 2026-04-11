#pragma once

#include "Tazel/Renderer/RendererAPI.hpp"
#include "Tazel/Renderer/RendererFrame.hpp"
#include "Tazel/Renderer/RenderPass.hpp"

namespace Tazel {

  class Mesh {
  public:
    std::vector<Vertex> Vertices;
    std::vector<uint32_t> Indices;

    void Bind(RenderPass& pass) {
      pass.BindVertexBuffer(*m_VertexBuffer);
      pass.BindIndexBuffer(*m_IndexBuffer);
    }

    void Draw(RenderPass& pass) {
      pass.DrawIndexed(m_IndexCount);
    }

    void SetVertexBuffer(std::shared_ptr<Buffer> vertexBuffer) {
      m_VertexBuffer = vertexBuffer;
    }

    void SetIndexBuffer(std::shared_ptr<Buffer> indexBuffer) {
      m_IndexBuffer = indexBuffer;
    }

    void SetIndexCount(uint32_t indexCount) {
      m_IndexCount = indexCount;
    }

  private:
    std::shared_ptr<Buffer> m_VertexBuffer = nullptr;
    std::shared_ptr<Buffer> m_IndexBuffer = nullptr;
    uint32_t m_IndexCount = 0;
  };

  class Material {
  public:
    template<typename T>
    void Set(const std::string& name, const T& value) {
      m_Data[name] = std::vector<uint8_t>((uint8_t*)&value,
					  (uint8_t*)&value + sizeof(T));
    }
    
    void Bind(RenderPass* pass) {
      for (auto& [name, data] : m_Data) {
	// pass->SetUniform(name, data.data(), data.size());
	TZ_CORE_ASSERT(false, "To be implemented");
      }
    }
    
  private:
    std::unordered_map<std::string, std::vector<uint8_t>> m_Data;
  };

  struct DrawCommand {
    Mesh* mesh;
    Material* material;
    glm::mat4 transform;
  };
  
  class Renderer {
  public:
    Renderer() = default;
    ~Renderer() = default;

    void Init(Window* window);

    void Begin();

    void Upload(Mesh* mesh);
    // TODO: To be implemented.
    void Submit(Mesh* mesh /*, Material* material, const glm::mat4& transform */);
    
    void End();

    void SetClearColor(glm::vec4 ClearColor) { m_ClearColor = ClearColor; }
    void SetWireFrame(bool wireframe) { useWireFrame = wireframe; }

  private:
    glm::vec4 m_ClearColor = {0.0f,0.0f,0.0f,1.0f};
    
    std::unique_ptr<RendererAPI> m_RendererAPI;
    std::shared_ptr<Pipeline> m_DefaultPipeline;
    std::shared_ptr<Pipeline> m_WireframePipeline;

    std::unique_ptr<RendererFrame> m_CurrentFrame;

    std::vector<DrawCommand> m_DrawQueue;

    bool useWireFrame = false;
  };

}
