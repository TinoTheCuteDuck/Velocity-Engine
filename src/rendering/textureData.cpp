#define STB_IMAGE_IMPLEMENTATION

#include "rendering/textureData.hpp"

#include "core/engine.hpp"
#include "stb_image.h"

TextureData::TextureData(const std::string& filePath, const TextureWrapMode wrapU, const TextureWrapMode wrapV, const TextureWrapMode wrapW, const TextureFilter minFilter, const TextureFilter magFilter, const bool mipmaps)
    : filePath(filePath), wrapU(wrapU), wrapV(wrapV), wrapW(wrapW), minFilter(minFilter), magFilter(magFilter), mipmaps(mipmaps) {
    constexpr RGBMode format[5] = {RGBMode::NONE, RGBMode::RED, RGBMode::RG, RGBMode::RGB, RGBMode::RGBA};

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    rgbMode = format[nrChannels];
}

TextureData::~TextureData() {
    if (data)
        stbi_image_free(data);
    if (textureId)
        Engine::get().renderer.deleteTexture(textureId);
}

TextureData::TextureData(TextureData&& other) noexcept {
    filePath = std::move(other.filePath);
    textureId = other.textureId;

    wrapU = other.wrapU;
    wrapV = other.wrapV;
    wrapW = other.wrapW;

    minFilter = other.minFilter;
    magFilter = other.magFilter;
    rgbMode = other.rgbMode;

    mipmaps = other.mipmaps;

    data = other.data;
    width = other.width;
    height = other.height;
    nrChannels = other.nrChannels;

    other.textureId = 0;
    other.data = nullptr;
}

TextureData& TextureData::operator=(TextureData&& other) noexcept {
    if (this != &other) {
        stbi_image_free(data);
        Engine::get().renderer.deleteTexture(textureId);

        filePath = std::move(other.filePath);
        textureId = other.textureId;

        wrapU = other.wrapU;
        wrapV = other.wrapV;
        wrapW = other.wrapW;

        minFilter = other.minFilter;
        magFilter = other.magFilter;
        rgbMode = other.rgbMode;

        mipmaps = other.mipmaps;

        data = other.data;
        width = other.width;
        height = other.height;
        nrChannels = other.nrChannels;

        other.textureId = 0;
        other.data = nullptr;
    }
    return *this;
}
