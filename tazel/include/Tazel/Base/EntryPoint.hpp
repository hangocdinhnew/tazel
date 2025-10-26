#pragma once

#include "Tazel/Base/Log.hpp"
#include "Tazel/Base/Application.hpp"

int main(int argc, char** argv)
{
  Tazel::Log::Init();
  TZ_CORE_INFO("Initialized Log!");
  
  Tazel::Application* app = Tazel::CreateApplication();
  app->Run();

  delete app;
}
