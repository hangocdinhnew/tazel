#include <cassert>

#include "Tazel/Base/Log.hpp"

#include "Platform/SDL/SDLRenderer.hpp"

namespace Tazel {

  static SDL_GPULoadOp ToSDLLoadOp(LoadOp op) {
    switch (op) {
    case LoadOp::Load:     return SDL_GPU_LOADOP_LOAD;
    case LoadOp::Clear:    return SDL_GPU_LOADOP_CLEAR;
    case LoadOp::DontCare: return SDL_GPU_LOADOP_DONT_CARE;
    }
    
    return SDL_GPU_LOADOP_LOAD;
  }
  
  static SDL_GPUStoreOp ToSDLStoreOp(StoreOp op) {
    switch (op) {
    case StoreOp::Store:    return SDL_GPU_STOREOP_STORE;
    case StoreOp::DontCare: return SDL_GPU_STOREOP_DONT_CARE;
    }
    
    return SDL_GPU_STOREOP_STORE;
  }
  
  SDLRenderer::SDLRenderer(Window* Window) : m_WindowHandle(Window) {
    TZ_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
  }
  
  void SDLRenderer::Init() {
    m_Instance = std::make_unique<SDLInstance>(m_WindowHandle);
    m_Instance->Init();
    
    m_SDLWindow = static_cast<SDLWindow*>(m_WindowHandle);
    TZ_CORE_ASSERT(m_SDLWindow, "Failed to get SDL Window!");
  }
  
  std::unique_ptr<RendererFrame> SDLRenderer::BeginFrame() {
    auto frame = std::make_unique<SDLFrame>();
    
    frame->CmdBuf = SDL_AcquireGPUCommandBuffer(m_Instance->GetGPUDevice());
    TZ_CORE_ASSERT(frame->CmdBuf, "Failed to acquire Command Buffer! Reason: '{}'", SDL_GetError());
    
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(frame->CmdBuf, m_SDLWindow->GetWindow(), &frame->BackBuffer, &w, &h))
      TZ_CORE_ASSERT(false, "Failed to wait and acquire Swapchain texture! Reason: '{}'", SDL_GetError());
    
    return frame;
  }
  
  void SDLRenderer::EndFrame(RendererFrame& baseFrame) {
    auto& sdlFrame = static_cast<SDLFrame&>(baseFrame);
    
    SDL_SubmitGPUCommandBuffer(sdlFrame.CmdBuf);
  }

  std::unique_ptr<RenderTexture> SDLRenderer::CreateTexture(const TextureDesc& desc) {
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

  void SDLRenderer::DestroyTexture(RenderTexture& texture) {
    auto& sdlTexture = static_cast<SDLTexture&>(texture);
    
    SDL_ReleaseGPUTexture(m_Instance->GetGPUDevice(), sdlTexture.Texture);
  }
  
  // Frame -> Render Pass
  
  std::unique_ptr<RenderPass> SDLFrame::BeginRenderPass(const RenderPassDesc& desc) {
    std::vector<SDL_GPUColorTargetInfo> colorInfos;
    colorInfos.reserve(desc.colorAttachments.size());
    
    for (size_t i = 0; i < desc.colorAttachments.size(); ++i) {
      const auto& attachment = desc.colorAttachments[i];

      SDL_GPUColorTargetInfo info{};

      SDL_GPUTexture* texture = BackBuffer;
      if (attachment.texture) {
	auto* sdlTexture = static_cast<SDLTexture*>(attachment.texture);
	
	texture = sdlTexture->Texture;
      }

      info.texture = texture;
      info.mip_level = 0;
      info.layer_or_depth_plane = 0;
      
      info.load_op  = ToSDLLoadOp(attachment.loadOp);
      info.store_op = ToSDLStoreOp(attachment.storeOp);
      
      if (attachment.loadOp == LoadOp::Clear) {
	info.clear_color.r = attachment.clearValue.r;
	info.clear_color.g = attachment.clearValue.g;
	info.clear_color.b = attachment.clearValue.b;
	info.clear_color.a = attachment.clearValue.a;
      }
      
      colorInfos.push_back(info);
    }
    
    SDL_GPUDepthStencilTargetInfo depthInfo{};
    SDL_GPUDepthStencilTargetInfo* depthPtr = nullptr;
    
    if (desc.depthStencilAttachment.has_value()) {
      assert(false && "Depth stencil not implemented yet!");
      
      const auto& depth = desc.depthStencilAttachment.value();
      
      depthInfo.texture = nullptr; // TODO: Implement depth stencil
      depthInfo.mip_level = 0;
      depthInfo.layer = 0;
      
      depthInfo.load_op         = ToSDLLoadOp(depth.depthLoadOp);
      depthInfo.store_op        = ToSDLStoreOp(depth.depthStoreOp);
      depthInfo.stencil_load_op = ToSDLLoadOp(depth.stencilLoadOp);
      depthInfo.stencil_store_op= ToSDLStoreOp(depth.stencilStoreOp);
      
      depthInfo.clear_depth   = depth.clearDepth;
      depthInfo.clear_stencil = depth.clearStencil;
      
      depthPtr = &depthInfo;
    }
    
    SDL_GPURenderPass* sdlPass = SDL_BeginGPURenderPass(CmdBuf,
							colorInfos.data(),
							(Uint32)colorInfos.size(),
							depthPtr);
    
    auto pass = std::make_unique<SDLPass>();
    pass->render_pass = sdlPass;
    
    return pass;
  }

  void SDLFrame::EndRenderPass(RenderPass& pass)
  {
    SDLPass& sdlPass = static_cast<SDLPass&>(pass);
    SDL_EndGPURenderPass(sdlPass.render_pass);

    sdlPass.render_pass = nullptr;
  }
  
}
