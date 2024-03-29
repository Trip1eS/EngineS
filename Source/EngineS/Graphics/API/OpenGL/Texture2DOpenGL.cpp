#include "Texture2DOpenGL.hpp"
#include "UtilsOpenGL.hpp"

namespace EngineS {

Texture2DOpenGL::~Texture2DOpenGL() {
    if (_texture) {
        glDeleteTextures(1, &_texture);
    }
}

void Texture2DOpenGL::Init(const TextureDescriptor& desc) {
    Texture2D::Init(desc);

    UtilsOpenGL::ConvertPixelFormat(desc.textureFormat, _internalFormat, _imageFormat, _dataType);

    _wrapS = UtilsOpenGL::ConvertAddressMode(desc.samplerDescriptor.sAddressMode);
    _wrapT = UtilsOpenGL::ConvertAddressMode(desc.samplerDescriptor.tAddressMode);

    _minFilter = UtilsOpenGL::ConvertFilter(desc.samplerDescriptor.minFilter);
    _magFilter = UtilsOpenGL::ConvertFilter(desc.samplerDescriptor.magFilter);

    if (_texture) {
        glDeleteTextures(1, &_texture);
    }
    glGenTextures(1, &_texture);

    UpdateData(desc.data, desc.width, desc.height);
    UtilsOpenGL::CheckError();
}

void Texture2DOpenGL::UpdateData(const byte* data, u32 width, u32 height) {
    Texture2D::UpdateData(data, width, height);

    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);

    glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, width, height, 0, _imageFormat, _dataType, data);

    UtilsOpenGL::CheckError();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2DOpenGL::Apply(u32 index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, _texture);
    UtilsOpenGL::CheckError();
}

} // namespace EngineS
