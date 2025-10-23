#include "Tazel.hpp"

class Sandbox : public Tazel::Application {
public:
  Sandbox() {}

  ~Sandbox() {}
};

Tazel::Application* Tazel::CreateApplication() {
  return new Sandbox();
}
