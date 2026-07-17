#include "core/assetManager.hpp"

#include "core/engine.hpp"
#include "rendering/OpenGL/renderer.hpp"
#include "rendering/textureData.hpp"

#include <string>
#include <thread>
#include <utility>
#include <variant>

AssetManager::AssetManager() {
    meshData.reserve(1024);
    textureData.reserve(1024);
    shaderData.reserve(1024);
}

void AssetManager::update() {
    Renderer& renderer = Engine::get().renderer;

    while (true) {
        auto item = queue.pop_back();

        if (!item)
            break;

        if (item->type == MESH) {
            if (std::holds_alternative<MeshData>(item->data)) {
                MeshData mesh = std::get<MeshData>(std::move(item->data));
                unsigned int meshId = renderer.addGPUMesh(mesh.vertexData, mesh.indices);
                mesh.meshId = meshId;

                loadingMeshData.erase(loadingMeshData.find(mesh.filePath));
                auto ptr = std::make_unique<MeshData>(std::move(mesh));
                meshData.emplace(ptr->filePath, std::move(ptr));
            }

        } else if (item->type == TEXTURE) {
            if (std::holds_alternative<TextureData>(item->data)) {
                TextureData texture = std::get<TextureData>(std::move(item->data));
                unsigned int textureId = renderer.addTexture(texture.data, texture.width, texture.height, texture.wrapU, texture.wrapV, texture.wrapW, texture.minFilter, texture.magFilter, texture.rgbMode, texture.mipmaps);
                texture.textureId = textureId;

                loadingTextureData.erase(loadingTextureData.find(texture.filePath));
                auto ptr = std::make_unique<TextureData>(std::move(texture));
                textureData.emplace(ptr->filePath, std::move(ptr));
            }

        } else if (item->type == SHADER) {
            if (std::holds_alternative<ShaderData>(item->data)) {
                ShaderData shader = std::get<ShaderData>(std::move(item->data));
                unsigned int shaderId = renderer.addShader(shader.vShaderSource, shader.fShaderSource);
                shader.shaderId = shaderId;

                std::string shaderKey = shader.vertexShaderPath + " | " + shader.fragmentShaderPath;

                loadingShaderData.erase(loadingShaderData.find(shaderKey));
                auto ptr = std::make_unique<ShaderData>(std::move(shader));
                shaderData.emplace(shaderKey, std::move(ptr));
            }
        }
    }
}

unsigned int AssetManager::loadMesh(const std::string& filePath) {
    if (meshData.contains(filePath)) {
        return meshData.at(filePath)->meshId;
    }

    if (loadingMeshData.contains(filePath)) {
        return 0;
    }

    loadingMeshData.insert(filePath);
    std::thread upload([this, filePath]() {
        this->loadThreadedMesh(filePath);
    });
    upload.detach();

    return 0;
}

unsigned int AssetManager::loadShader(const std::string& vShaderPath, const std::string& fShaderPath) {
    const std::string shaderKey = vShaderPath + " | " + fShaderPath;
    if (shaderData.contains(shaderKey)) {
        return shaderData.at(shaderKey)->shaderId;
    }

    if (loadingShaderData.contains(shaderKey)) {
        return 0;
    }

    loadingShaderData.insert(shaderKey);
    std::thread upload([this, vShaderPath, fShaderPath] {
        this->loadThreadedShader(vShaderPath, fShaderPath);
    });
    upload.detach();

    return 0;
}

unsigned int AssetManager::loadTexture(const std::string& filePath, TextureWrapMode wrapU, TextureWrapMode wrapV, TextureWrapMode wrapW, TextureFilter minFilter, TextureFilter magFilter, bool mipmaps) {
    if (textureData.contains(filePath)) {
        return textureData.at(filePath)->textureId;
    }

    if (loadingTextureData.contains(filePath)) {
        return 0;
    }

    loadingTextureData.insert(filePath);
    std::thread upload([this, filePath, wrapU, wrapV, wrapW, minFilter, magFilter, mipmaps]() {
        this->loadThreadedTexture(filePath, wrapU, wrapV, wrapW, minFilter, magFilter, mipmaps);
    });
    upload.detach();
    return 0;
}

MeshData* AssetManager::getMesh(const std::string& filePath) const {
    if (meshData.contains(filePath)) {
        return meshData.at(filePath).get();
    }
    return nullptr;
}

ShaderData* AssetManager::getShader(const std::string& vShaderPath, const std::string& fShaderPath) const {
    if (const std::string key = vShaderPath + " | " + fShaderPath; shaderData.contains(key)) {
        return shaderData.at(key).get();
    }
    return nullptr;
}
TextureData* AssetManager::getTexture(const std::string& filePath) const {
    if (textureData.contains(filePath)) {
        return textureData.at(filePath).get();
    }
    return nullptr;
}

void AssetManager::loadThreadedMesh(const std::string& filePath) {
    MeshData mesh(filePath);
    queue.push_back(LoadRequest{.data = std::move(mesh), .type = MESH});
}

void AssetManager::loadThreadedShader(std::string vShaderPath, std::string fShaderPath) {
    ShaderData shader(std::move(vShaderPath), std::move(fShaderPath));
    queue.push_back(LoadRequest{.data = std::move(shader), .type = SHADER});
}

void AssetManager::loadThreadedTexture(std::string filePath, const TextureWrapMode wrapU, const TextureWrapMode wrapV, const TextureWrapMode wrapW, const TextureFilter minFilter, const TextureFilter magFilter, const bool mipmaps) {
    TextureData texture(std::move(filePath), wrapU, wrapV, wrapW, minFilter, magFilter, mipmaps);
    queue.push_back(LoadRequest{.data = std::move(texture), .type = TEXTURE});
}