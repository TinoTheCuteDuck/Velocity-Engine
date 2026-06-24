#include "rendering/OpenGL/OpenGLTexture.hpp"

#include "glad/glad.h"
#include "rendering/textureData.hpp"

GLenum wrapToGL(TextureWrapMode mode) {
    switch (mode) {
    case TextureWrapMode::Repeat:
        return GL_REPEAT;
    case TextureWrapMode::ClampToEdge:
        return GL_CLAMP_TO_EDGE;
    case TextureWrapMode::MirroredRepeat:
        return GL_MIRRORED_REPEAT;
    case TextureWrapMode::ClampToBorder:
        return GL_CLAMP_TO_BORDER;
    }
    return GL_REPEAT;
};

GLenum filterToGL(TextureFilter mode, bool mipmaps) {
    switch (mode) {
    case TextureFilter::Linear:
        return mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
    case TextureFilter::Nearest:
        return mipmaps ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
    }
    return GL_LINEAR;
}

GLenum modeToGL(RGBMode mode) {
    switch (mode) {
    case RGBMode::NONE:
        return GL_RGBA;
    case RGBMode::RED:
        return GL_RED;
    case RGBMode::RG:
        return GL_RG;
    case RGBMode::RGB:
        return GL_RGB;
    case RGBMode::RGBA:
        return GL_RGBA;
    }
    return GL_RGBA;
}

OpenGLTexture::OpenGLTexture(
    unsigned char* data,
    unsigned int width,
    unsigned int height,
    TextureWrapMode wrapU,
    TextureWrapMode wrapV,
    TextureWrapMode wrapW,
    TextureFilter minFilter,
    TextureFilter magFilter,
    RGBMode rgbMode,
    bool mipmaps) {

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapToGL(wrapU));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapToGL(wrapV));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapToGL(wrapW));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterToGL(minFilter, mipmaps));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterToGL(magFilter, false));

    glTexImage2D(GL_TEXTURE_2D, 0, modeToGL(rgbMode), width, height, 0, modeToGL(rgbMode), GL_UNSIGNED_BYTE, data);

    if (mipmaps)
        glGenerateMipmap(GL_TEXTURE_2D);
}

OpenGLTexture::~OpenGLTexture() {
    glDeleteTextures(1, &texture);
}

OpenGLTexture::OpenGLTexture(OpenGLTexture&& other) noexcept {
    texture = other.texture;
    other.texture = 0;
}

void OpenGLTexture::bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);
}