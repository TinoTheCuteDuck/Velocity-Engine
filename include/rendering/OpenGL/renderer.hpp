#pragma once

#include "core/idAllocator.hpp"
#include "math/matrices/mat4.hpp"
#include "rendering/OpenGL/OpenGLMesh.hpp"
#include "rendering/OpenGL/OpenGLShader.hpp"
#include "rendering/OpenGL/OpenGLTexture.hpp"
#include "rendering/material.hpp"
#include "rendering/textureData.hpp"

#include <optional>
#include <unordered_map>
#include <vector>

struct UiVertex;
struct WidgetData;
struct Vertex;

struct RenderCall {
    unsigned int meshID;
    Material material;
    std::optional<Mat4> transform = std::nullopt;
    std::optional<bool> depthTest = true;
};

class Renderer {
  public:
    Renderer();
    void renderQueue(RenderCall cmd);
    void startFrame();
    void endFrame();

    unsigned int addGPUMesh(std::vector<Vertex>& vertexData, std::vector<unsigned int>& indices);
    void deleteGPUMesh(const unsigned int meshID);

    unsigned int addGPUUiMesh(const size_t memory);
    void changeGPUUiMeshData(const unsigned int meshID, const unsigned int elementID, const size_t offset, const size_t memory, std::vector<UiVertex>& vertexData, WidgetData& widgetData);

    unsigned int addShader(std::string vShaderSource, std::string fShaderSource);
    void deleteShader(const unsigned int shaderID);

    unsigned int addTexture(unsigned char* data, unsigned int width, unsigned int height, TextureWrapMode wrapU, TextureWrapMode wrapV, TextureWrapMode wrapW, TextureFilter minFilter, TextureFilter magFilter, RGBMode rgbMode, bool mipmaps);
    void deleteTexture(const unsigned int textureID);

    void enableWireframe(bool state);
    bool getWireframeEnabled();

  private:
    bool wireframeEnabled = false;

    std::vector<RenderCall> commands;
    std::unordered_map<unsigned int, OpenGLMesh> meshes;
    std::unordered_map<unsigned int, OpenGLShader> shaders;
    std::unordered_map<unsigned int, OpenGLTexture> textures;

    IDAllocator meshIdAllocator = IDAllocator(1024);
    IDAllocator shaderIDAllocator = IDAllocator(1024);
    IDAllocator textureIDAllocator = IDAllocator(1024);
};