enum class RendererAPI {
  None = 0,
  SDLGPU,
};

static RendererAPI GetRendererAPI()
{
  return RendererAPI::SDLGPU;
}
