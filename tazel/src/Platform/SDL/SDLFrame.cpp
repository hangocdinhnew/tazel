#include <cassert>

#include "Tazel/Base/Log.hpp"

#include "Platform/SDL/SDLTexture.hpp"
#include "Platform/SDL/SDLPass.hpp"
#include "Platform/SDL/SDLFrame.hpp"

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

  SDLFrame::~SDLFrame() {
    SDL_SubmitGPUCommandBuffer(CmdBuf);
  }

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

}
