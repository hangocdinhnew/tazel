#pragma once

#include "Tazel/Application.hpp"

int main(int argc, char** argv)
{
  Tazel::Application* app = Tazel::CreateApplication();
  app->Run();

  delete app;
}
