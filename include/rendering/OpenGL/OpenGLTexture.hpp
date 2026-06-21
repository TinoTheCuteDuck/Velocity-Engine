#pragma once

#include "glad/glad.h"
#include "rendering/textureData.hpp"

class OpenGLTexture {
  public:
    OpenGLTexture(
        unsigned char* data,
        unsigned int width,
        unsigned int height,
        TextureWrapMode wrapU,
        TextureWrapMode wrapV,
        TextureWrapMode wrapW,
        TextureFilter minFilter,
        TextureFilter magFilter,
        RGBMode rgbMode,
        bool mipmaps);

    ~OpenGLTexture();
    OpenGLTexture(OpenGLTexture&& other) noexcept;

  public:
    unsigned int texture;

  public:
    void bind(unsigned int slot);
};