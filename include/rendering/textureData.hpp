#pragma once

#include <string>

enum class TextureWrapMode {
    Repeat,
    ClampToEdge,
    MirroredRepeat,
    ClampToBorder
};

enum class TextureFilter {
    Nearest,
    Linear
};

enum class RGBMode {
    NONE,
    RED,
    RG,
    RGB,
    RGBA
};

class TextureData {
  public:
    TextureData(const std::string filePath,
                TextureWrapMode wrapU = TextureWrapMode::Repeat,
                TextureWrapMode wrapV = TextureWrapMode::Repeat,
                TextureWrapMode wrapW = TextureWrapMode::Repeat,
                TextureFilter minFilter = TextureFilter::Linear,
                TextureFilter magFilter = TextureFilter::Linear,
                bool mipmaps = true);
    ~TextureData();

    TextureData(const TextureData&) = delete;
    TextureData& operator=(const TextureData&) = delete;

    TextureData(TextureData&& other) noexcept;
    TextureData& operator=(TextureData&& other) noexcept;

  public:
    std::string filePath;
    unsigned int textureId = 0;

    TextureWrapMode wrapU;
    TextureWrapMode wrapV;
    TextureWrapMode wrapW;

    TextureFilter minFilter;
    TextureFilter magFilter;
    RGBMode rgbMode;

    bool mipmaps;

    unsigned char* data;
    int width, height;
    int nrChannels;
};