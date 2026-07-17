#pragma once

#include "core/threadSafeVector.hpp"
#include "rendering/meshData.hpp"
#include "rendering/shaderData.hpp"
#include "rendering/textureData.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>

enum AssetType {
    MESH,
    SHADER,
    TEXTURE
};

struct LoadRequest {
    std::variant<MeshData, TextureData, ShaderData> data;
    AssetType type;
};

class AssetManager {
  public:
    AssetManager();

  public:
    void update();
    unsigned int loadMesh(const std::string& filePath);
    unsigned int loadShader(const std::string& vShaderPath, const std::string& fShaderPath);
    unsigned int loadTexture(const std::string& filePath, TextureWrapMode wrapU = TextureWrapMode::Repeat, TextureWrapMode wrapV = TextureWrapMode::Repeat, TextureWrapMode wrapW = TextureWrapMode::Repeat, TextureFilter minFilter = TextureFilter::Linear, TextureFilter magFilter = TextureFilter::Linear, bool mipmaps = true);

    MeshData* getMesh(const std::string& filePath) const;
    ShaderData* getShader(const std::string& vShaderPath, const std::string& fShaderPath) const;
    TextureData* getTexture(const std::string& filePath) const;

  private:
    void loadThreadedMesh(const std::string& filePath);
    void loadThreadedShader(std::string vShaderPath, std::string fShaderPath);
    void loadThreadedTexture(std::string filePath, TextureWrapMode wrapU, TextureWrapMode wrapV, TextureWrapMode wrapW, TextureFilter minFilter, TextureFilter magFilter, bool mipmaps);

  private:
    std::unordered_map<std::string, std::unique_ptr<MeshData>> meshData;
    std::unordered_map<std::string, std::unique_ptr<TextureData>> textureData;
    std::unordered_map<std::string, std::unique_ptr<ShaderData>> shaderData;

    std::unordered_set<std::string> loadingMeshData;
    std::unordered_set<std::string> loadingTextureData;
    std::unordered_set<std::string> loadingShaderData;

    ThreadSafeVector<LoadRequest> queue;
};