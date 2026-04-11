#include "Tazel.hpp"

class ExampleLayer : public Tazel::Layer {
public:

  Tazel::Mesh cube;

  ExampleLayer()
    : Layer("Example")
  {
  }
  
  void OnUpdate() override {}
  
  void OnEvent(Tazel::Event& event) override {}

  void OnRun(Tazel::Renderer& renderer) override {
    cube.Vertices = {
      {{-0.5f, -0.5f, -0.5f}}, // 0
      {{ 0.5f, -0.5f, -0.5f}}, // 1
      {{ 0.5f,  0.5f, -0.5f}}, // 2
      {{-0.5f,  0.5f, -0.5f}}, // 3
      {{-0.5f, -0.5f,  0.5f}}, // 4
      {{ 0.5f, -0.5f,  0.5f}}, // 5
      {{ 0.5f,  0.5f,  0.5f}}, // 6
      {{-0.5f,  0.5f,  0.5f}}  // 7
    };

    cube.Indices = {
      // back (-Z)
      0, 1, 2,
      2, 3, 0,
      
      // front (+Z)
      4, 5, 6,
      6, 7, 4,
      
      // left (-X)
      0, 3, 7,
      7, 4, 0,
      
      // right (+X)
      1, 5, 6,
      6, 2, 1,
      
      // bottom (-Y)
      0, 1, 5,
      5, 4, 0,
      
      // top (+Y)
      3, 2, 6,
      6, 7, 3
    };

    renderer.Upload(&cube); // Upload
  }

  void OnRender(Tazel::Renderer& renderer) override { // Flight
    renderer.Submit(&cube);
  }

};

class Sandbox : public Tazel::Application {
public:

  Sandbox() {
    PushLayer(new ExampleLayer());
  }

  ~Sandbox() {}

};

Tazel::Application* Tazel::CreateApplication()
{
  return new Sandbox();
}
