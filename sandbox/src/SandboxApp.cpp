#include "Tazel.hpp"

class ExampleLayer : public Tazel::Layer {
public:

  ExampleLayer()
    : Layer("Example")
  {
  }
  
  void OnUpdate() override {}
  
  void OnEvent(Tazel::Event& event) override {}

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
