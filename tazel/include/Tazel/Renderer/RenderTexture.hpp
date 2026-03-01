#pragma once

#include <memory>
#include <optional>

#include <glm/glm.hpp>

#include "Tazel/Base/Window.hpp"

namespace Tazel {

  enum class TextureType {
    TwoD,
    TwoDArray,
    ThreeD,
    Cube,
    CubeArray 
  };
  
  enum class TextureFormat {
    Invalid,
     
    A8Unorm,
    R8Unorm,
    R8G8Unorm,
    R8G8B8A8Unorm,
    R16Unorm,
    R16G16Unorm,
    R16G16B16A16Unorm,
    R10G10B10A2Unorm,
    B5G6R5Unorm,
    B5G5R5A1Unorm,
    B4G4R4A4Unorm,
    B8G8R8A8Unorm,
     
    Bc1RgbaUnorm,
    Bc2RgbaUnorm,
    Bc3RgbaUnorm,
    Bc4RUnorm,
    Bc5RgUnorm,
    Bc7RgbaUnorm,
     
    Bc6HRgbFloat,
     
    Bc6HRgbUfloat,
     
    R8Snorm,
    R8G8Snorm,
    R8G8B8A8Snorm,
    R16Snorm,
    R16G16Snorm,
    R16G16B16A16Snorm,
     
    R16Float,
    R16G16Float,
    R16G16B16A16Float,
    R32Float,
    R32G32Float,
    R32G32B32A32Float,
     
    R11G11B10Ufloat,
     
    R8Uint,
    R8G8Uint,
    R8G8B8A8Uint,
    R16Uint,
    R16G16Uint,
    R16G16B16A16Uint,
    R32Uint,
    R32G32Uint,
    R32G32B32A32Uint,
    R8Int,
    R8G8Int,
    R8G8B8A8Int,
    R16Int,
    R16G16Int,
    R16G16B16A16Int,
    R32Int,
    R32G32Int,
    R32G32B32A32Int,
     
    R8G8B8A8UnormSrgb,
    B8G8R8A8UnormSrgb,
     
    Bc1RgbaUnormSrgb,
    Bc2RgbaUnormSrgb,
    Bc3RgbaUnormSrgb,
    Bc7RgbaUnormSrgb,
     
    D16Unorm,
    D24Unorm,
    D32Float,
    D24UnormS8Uint,
    D32FloatS8Uint,
     
    Astc_4x4Unorm,
    Astc_5x4Unorm,
    Astc_5x5Unorm,
    Astc_6x5Unorm,
    Astc_6x6Unorm,
    Astc_8x5Unorm,
    Astc_8x6Unorm,
    Astc_8x8Unorm,
    Astc_10x5Unorm,
    Astc_10x6Unorm,
    Astc_10x8Unorm,
    Astc_10x10Unorm,
    Astc_12x10Unorm,
    Astc_12x12Unorm,
     
    Astc_4x4UnormSrgb,
    Astc_5x4UnormSrgb,
    Astc_5x5UnormSrgb,
    Astc_6x5UnormSrgb,
    Astc_6x6UnormSrgb,
    Astc_8x5UnormSrgb,
    Astc_8x6UnormSrgb,
    Astc_8x8UnormSrgb,
    Astc_10x5UnormSrgb,
    Astc_10x6UnormSrgb,
    Astc_10x8UnormSrgb,
    Astc_10x10UnormSrgb,
    Astc_12x10UnormSrgb,
    Astc_12x12UnormSrgb,
     
    Astc_4x4Float,
    Astc_5x4Float,
    Astc_5x5Float,
    Astc_6x5Float,
    Astc_6x6Float,
    Astc_8x5Float,
    Astc_8x6Float,
    Astc_8x8Float,
    Astc_10x5Float,
    Astc_10x6Float,
    Astc_10x8Float,
    Astc_10x10Float,
    Astc_12x10Float,
    Astc_12x12Float
  };

  enum class TextureUsage : uint32_t {
    None                          = 0,
    Sampler                       = 1u << 0,
    ColorTarget                   = 1u << 1,
    DepthStencilTarget            = 1u << 2,
    GraphicsStorageRead           = 1u << 3,
    ComputeStorageRead            = 1u << 4,
    ComputeStorageWrite           = 1u << 5,
    ComputeStorageSimultaneousRW  = 1u << 6
  };

  inline TextureUsage operator|(TextureUsage a, TextureUsage b) {
    return static_cast<TextureUsage>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
  }
  
  inline TextureUsage operator&(TextureUsage a, TextureUsage b) {
    return static_cast<TextureUsage>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
  }
  
  inline TextureUsage& operator|=(TextureUsage& a, TextureUsage b) {
    a = a | b;
    return a;
  }

  enum class GPUSampleCount {
    None,
    MSAA2x,
    MSAA4x,
    MSAA8x
  };
  
  struct TextureDesc {
    TextureType type = TextureType::TwoD;
    TextureFormat format = TextureFormat::Invalid;
    TextureUsage usage = TextureUsage::ColorTarget;

    unsigned int width = 0;
    unsigned int height = 0;

    GPUSampleCount sample = GPUSampleCount::None;
  };

  class RenderTexture {
  public:
    virtual ~RenderTexture() = default;
  };
}
