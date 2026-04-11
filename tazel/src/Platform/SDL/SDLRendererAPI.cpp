#include <cassert>

#include "Tazel/Base/Log.hpp"

#include "Platform/SDL/SDLRendererAPI.hpp"

namespace Tazel {

  SDLRendererAPI::SDLRendererAPI(Window* Window) : m_WindowHandle(Window) {
    TZ_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
  }
  
  void SDLRendererAPI::Init() {
    m_Instance = std::make_unique<SDLInstance>(m_WindowHandle);
    m_Instance->Init();
    
    m_SDLWindow = static_cast<SDLWindow*>(m_WindowHandle);
    TZ_CORE_ASSERT(m_SDLWindow, "Failed to get SDL Window!");
  }
  
  std::unique_ptr<RendererFrame> SDLRendererAPI::BeginFrame() {
    auto frame = std::make_unique<SDLFrame>();
    
    frame->CmdBuf = SDL_AcquireGPUCommandBuffer(m_Instance->GetGPUDevice());
    TZ_CORE_ASSERT(frame->CmdBuf, "Failed to acquire Command Buffer! Reason: '{}'", SDL_GetError());
    
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(frame->CmdBuf, m_SDLWindow->GetWindow(), &frame->BackBuffer, &w, &h))
      TZ_CORE_ASSERT(false, "Failed to wait and acquire Swapchain texture! Reason: '{}'", SDL_GetError());
    
    return frame;
  }
  
  void SDLRendererAPI::EndFrame(RendererFrame& baseFrame) {
    auto& sdlFrame = static_cast<SDLFrame&>(baseFrame);
    
    SDL_SubmitGPUCommandBuffer(sdlFrame.CmdBuf);
  }

  std::unique_ptr<RenderTexture> SDLRendererAPI::CreateTexture(const TextureDesc& desc) {
    auto sdlTexture = std::make_unique<SDLTexture>();

    auto format = desc.format;
    
    if (format == TextureFormat::Invalid)
      format = static_cast<TextureFormat>(SDL_GetGPUSwapchainTextureFormat(m_Instance->GetGPUDevice(), m_SDLWindow->GetWindow()));

    unsigned int nw = desc.width;
    unsigned int nh = desc.height;

    if (nw == 0 || nh == 0) {
      TZ_CORE_ASSERT(w != 0 && h != 0, "Width and height of swapchain texture is zero! Make sure you have called CreateTexture **AFTER** BeginFrame");
      
      nw = w;
      nh = h;
    }
      
    const SDL_GPUTextureCreateInfo createInfo = {
      .type = static_cast<SDL_GPUTextureType>(desc.type),
      .format = static_cast<SDL_GPUTextureFormat>(format),
      .usage = static_cast<SDL_GPUTextureUsageFlags>(desc.usage),

      .width = nw,
      .height = nh,

      .sample_count = static_cast<SDL_GPUSampleCount>(desc.sample)
    };

    sdlTexture->Texture = SDL_CreateGPUTexture(m_Instance->GetGPUDevice(), &createInfo);

    return sdlTexture;
  }

  void SDLRendererAPI::DestroyTexture(RenderTexture& texture) {
    auto& sdlTexture = static_cast<SDLTexture&>(texture);
    
    SDL_ReleaseGPUTexture(m_Instance->GetGPUDevice(), sdlTexture.Texture);
  }

  std::shared_ptr<Pipeline> SDLRendererAPI::CreatePipeline(const ShaderDesc& vert, const ShaderDesc& frag, FillMode fillmode) {
    auto pipeline = std::make_shared<SDLPipeline>();

    pipeline->device = m_Instance->GetGPUDevice();

#ifdef __APPLE__
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_MSL;
#else
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_SPIRV;
#endif

    SDL_GPUShaderCreateInfo vertInfo{};
    vertInfo.code_size = vert.size;
    vertInfo.code = vert.data;
    vertInfo.entrypoint = "main";
    vertInfo.format = format;
    vertInfo.stage = SDL_GPU_SHADERSTAGE_VERTEX;
    vertInfo.num_samplers = vert.numSamplers;
    vertInfo.num_storage_textures = vert.numStorageTextures;
    vertInfo.num_storage_buffers = vert.numStorageBuffers;
    vertInfo.num_uniform_buffers = vert.numUniformBuffers;

    SDL_GPUShader* vertShader = SDL_CreateGPUShader(pipeline->device, &vertInfo);  
    TZ_CORE_ASSERT(vertShader, "Failed to create Vertex Shader, reason: {}", SDL_GetError());

    SDL_GPUShaderCreateInfo fragInfo{};
    fragInfo.code_size = frag.size;
    fragInfo.code = frag.data;
    fragInfo.entrypoint = "main";
    fragInfo.format = format;
    fragInfo.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    fragInfo.num_samplers = frag.numSamplers;
    fragInfo.num_storage_textures = frag.numStorageTextures;
    fragInfo.num_storage_buffers = frag.numStorageBuffers;
    fragInfo.num_uniform_buffers = frag.numUniformBuffers;

    SDL_GPUShader* fragShader = SDL_CreateGPUShader(pipeline->device, &fragInfo);  
    TZ_CORE_ASSERT(fragShader, "Failed to create Fragment Shader, reason: {}", SDL_GetError());

    SDL_GPUVertexBufferDescription vertexBufferDesc{};
    vertexBufferDesc.slot = 0;
    vertexBufferDesc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    vertexBufferDesc.instance_step_rate = 0;
    vertexBufferDesc.pitch = sizeof(Vertex);
    
    SDL_GPUVertexAttribute vertexAttr{};
    vertexAttr.buffer_slot = 0;
    vertexAttr.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertexAttr.location = 0;
    vertexAttr.offset = 0;

    SDL_GPUVertexInputState vertexInput{};
    vertexInput.num_vertex_buffers = 1;
    vertexInput.vertex_buffer_descriptions = &vertexBufferDesc;
    vertexInput.num_vertex_attributes = 1;
    vertexInput.vertex_attributes = &vertexAttr;

    SDL_GPUColorTargetDescription colorTarget{};
    colorTarget.format = SDL_GetGPUSwapchainTextureFormat(pipeline->device, m_SDLWindow->GetWindow());

    SDL_GPUGraphicsPipelineTargetInfo targetInfo{};
    targetInfo.num_color_targets = 1;
    targetInfo.color_target_descriptions = &colorTarget;

    SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo{};
    pipelineCreateInfo.target_info = targetInfo;
    pipelineCreateInfo.vertex_input_state = vertexInput;
    pipelineCreateInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
    pipelineCreateInfo.vertex_shader = vertShader;
    pipelineCreateInfo.fragment_shader = fragShader;

    if (fillmode == FillMode::Fill)
      pipelineCreateInfo.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_FILL;
    else
      pipelineCreateInfo.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_LINE;
      
    pipeline->pipeline = SDL_CreateGPUGraphicsPipeline(pipeline->device, &pipelineCreateInfo);
    TZ_CORE_ASSERT(pipeline->pipeline, "Failed to create GPU Graphics Pipeline, reason: {}", SDL_GetError());

    SDL_ReleaseGPUShader(pipeline->device, vertShader);
    SDL_ReleaseGPUShader(pipeline->device, fragShader);

    return pipeline;
  }

  std::shared_ptr<Buffer> SDLRendererAPI::CreateVertexBuffer(const void* data, size_t size) {
    TZ_CORE_ASSERT(size <= UINT32_MAX, "Buffer too large!");
    
    auto buffer = std::make_shared<SDLBuffer>();

    buffer->device = m_Instance->GetGPUDevice();

    SDL_GPUBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
    bufferCreateInfo.size = (uint32_t)size;
    buffer->buffer = SDL_CreateGPUBuffer(buffer->device, &bufferCreateInfo);
    TZ_CORE_ASSERT(buffer->buffer, "Failed to create Vertex Buffer, reason: {}", SDL_GetError());

    SDL_GPUTransferBufferCreateInfo transferBufferInfo{};
    transferBufferInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    transferBufferInfo.size = (uint32_t)size;
    SDL_GPUTransferBuffer* transfer = SDL_CreateGPUTransferBuffer(buffer->device, &transferBufferInfo);
    TZ_CORE_ASSERT(transfer, "Failed to create Transfer Buffer, reason: {}", SDL_GetError());

    void* ptr = SDL_MapGPUTransferBuffer(buffer->device, transfer, true);
    TZ_CORE_ASSERT(ptr, "Failed to map Transfer Buffer, reason: {}", SDL_GetError());
    memcpy(ptr, data, size);
    SDL_UnmapGPUTransferBuffer(buffer->device, transfer);

    SDL_GPUTransferBufferLocation transferBufferLocation{};
    transferBufferLocation.transfer_buffer = transfer;
    transferBufferLocation.offset = 0;

    SDL_GPUBufferRegion bufferRegion{};
    bufferRegion.buffer = buffer->buffer;
    bufferRegion.offset = 0;
    bufferRegion.size = (uint32_t)size;

    SDL_GPUCommandBuffer* cmdBuf = SDL_AcquireGPUCommandBuffer(buffer->device);
    SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(cmdBuf);
    
    SDL_UploadToGPUBuffer(copyPass,
			  &transferBufferLocation,
			  &bufferRegion,
			  false);

    SDL_EndGPUCopyPass(copyPass);
    SDL_SubmitGPUCommandBuffer(cmdBuf);
    SDL_ReleaseGPUTransferBuffer(buffer->device, transfer);

    return buffer;
  }
  
  std::shared_ptr<Buffer> SDLRendererAPI::CreateIndexBuffer(const void* data, size_t size) {
    TZ_CORE_ASSERT(size <= UINT32_MAX, "Buffer too large!");
    
    auto buffer = std::make_shared<SDLBuffer>();

    buffer->device = m_Instance->GetGPUDevice();

    SDL_GPUBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.usage = SDL_GPU_BUFFERUSAGE_INDEX;
    bufferCreateInfo.size = (uint32_t)size;
    buffer->buffer = SDL_CreateGPUBuffer(buffer->device, &bufferCreateInfo);
    TZ_CORE_ASSERT(buffer->buffer, "Failed to create Index Buffer, reason: {}", SDL_GetError());

    SDL_GPUTransferBufferCreateInfo transferBufferInfo{};
    transferBufferInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    transferBufferInfo.size = (uint32_t)size;
    SDL_GPUTransferBuffer* transfer = SDL_CreateGPUTransferBuffer(buffer->device, &transferBufferInfo);
    TZ_CORE_ASSERT(transfer, "Failed to create Transfer Buffer, reason: {}", SDL_GetError());

    void* ptr = SDL_MapGPUTransferBuffer(buffer->device, transfer, true);
    TZ_CORE_ASSERT(ptr, "Failed to map Transfer Buffer, reason: {}", SDL_GetError());
    memcpy(ptr, data, size);
    SDL_UnmapGPUTransferBuffer(buffer->device, transfer);

    SDL_GPUTransferBufferLocation transferBufferLocation{};
    transferBufferLocation.transfer_buffer = transfer;
    transferBufferLocation.offset = 0;

    SDL_GPUBufferRegion bufferRegion{};
    bufferRegion.buffer = buffer->buffer;
    bufferRegion.offset = 0;
    bufferRegion.size = (uint32_t)size;

    SDL_GPUCommandBuffer* cmdBuf = SDL_AcquireGPUCommandBuffer(buffer->device);
    SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(cmdBuf);
    
    SDL_UploadToGPUBuffer(copyPass,
			  &transferBufferLocation,
			  &bufferRegion,
			  false);

    SDL_EndGPUCopyPass(copyPass);
    bool ok = SDL_SubmitGPUCommandBuffer(cmdBuf);
    TZ_CORE_ASSERT(ok, "Failed to submit GPU command buffer: {}", SDL_GetError());
   
    SDL_ReleaseGPUTransferBuffer(buffer->device, transfer);

    return buffer;
  }
  
}
