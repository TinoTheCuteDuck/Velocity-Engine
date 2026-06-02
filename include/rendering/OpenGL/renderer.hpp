#pragma once

#include <core/idAllocator.hpp>
#include <glad/glad.h>
#include <math/matrices/mat4.hpp>
#include <optional>
#include <rendering/OpenGL/shader.hpp>
#include <rendering/OpenGL/texture.hpp>
#include <rendering/camera.hpp>
#include <rendering/material.hpp>
#include <string>
#include <ui/uiStructs.hpp>
#include <unordered_map>
#include <vector>

struct RenderCall {
    unsigned int meshID;
    Material material;
    std::optional<Mat4> transform = std::nullopt;
    std::optional<bool> depthTest = true;
};

struct GPUMesh {
    unsigned int VAO, VBO, EBO, UBO;
    size_t vertexCount;
    ~GPUMesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        if (EBO != 0) {
            glDeleteBuffers(1, &EBO);
        }
        if (UBO != 0) {
            glDeleteBuffers(1, &UBO);
        }
    }
};

struct Vertex;

class Renderer {
  public:
    Renderer();
    void renderQueue(RenderCall cmd);
    void startFrame();
    void endFrame();

    unsigned int addGPUMesh(const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indices);
    void deleteGPUMesh(const unsigned int meshID);
    void changeGPUMeshData(const unsigned int meshID, const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indices);

    unsigned int addGPUUiMesh(const size_t memory);
    void changeGPUUiMeshData(const unsigned int meshID, const unsigned int elementID, const size_t offset, const size_t memory, const std::vector<UiVertex>& vertexData, WidgetData& widgetData);

    unsigned int addShader(const std::string& vertexPath, const std::string& fragmentPath);
    void deleteShader(const unsigned int shaderID);

    unsigned int addTexture(const std::string& filepath, GLenum wrapMode, GLenum filterMode, bool generateMipmaps);
    void deleteTexture(const unsigned int textureID);

    void enableWireframe(bool state);
    bool getWireframeEnabled();

  private:
    bool wireframeEnabled = false;

    std::vector<RenderCall> commands;
    std::unordered_map<unsigned int, GPUMesh> meshes;
    std::unordered_map<unsigned int, Shader> shaders;
    std::unordered_map<unsigned int, Texture> textures;

    IDAllocator meshIdAllocator = IDAllocator(1024);
    IDAllocator shaderIDAllocator = IDAllocator(1024);
    IDAllocator textureIDAllocator = IDAllocator(1024);
};