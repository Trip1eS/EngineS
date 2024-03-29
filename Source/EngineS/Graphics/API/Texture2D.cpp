#include "Texture2D.hpp"

#include "Core/Macros.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace EngineS {

bool Texture2D::Load(const std::filesystem::path& path) {
    int  width, height, nrChannels;
    auto data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        Logger::Error("Failed to load image");
        return false;
    }

    if (nrChannels == 4) {
        _format = PixelFormat::RGBA8888;
    } else {
        _format = PixelFormat::RGB888;
    }
    _width  = width;
    _height = height;

    TextureDescriptor desc {
        .textureType       = TextureType::Texture2D,
        .textureFormat     = _format,
        .textureUsage      = TextureUsage::Read,
        .width             = _width,
        .height            = _height,
        .samplerDescriptor = {},
        .data              = reinterpret_cast<const byte*>(data),
    };
    Init(desc);

    stbi_image_free(data);
    return true;
}

void Texture2D::Init(const TextureDescriptor& desc) {
    _width  = desc.width;
    _height = desc.height;
    _format = desc.textureFormat;
}

void Texture2D::UpdateData(const byte* data, u32 width, u32 height) {
    _width  = width;
    _height = height;
}

} // namespace EngineS