#pragma once

#include "core/idAllocator.hpp"
#include "rendering/OpenGL/OpenGLMesh.hpp"
#include "rendering/OpenGL/OpenGLShader.hpp"
#include "rendering/OpenGL/OpenGLTexture.hpp"
#include "rendering/renderingTypes.hpp"
#include "rendering/textureData.hpp"

#include <unordered_map>
#include <vector>

struct UiVertex;
struct WidgetData;
struct Vertex;
struct RenderCall;

class Renderer {
  public:
    Renderer();
    ~Renderer();

  public:
    LightRenderCall lightCall;

    void renderQueue(RenderCall cmd);
    void startFrame() const;
    void endFrame();

    unsigned int addGPUMesh(std::vector<Vertex>& vertexData, std::vector<unsigned int>& indices);
    void deleteGPUMesh(unsigned int meshId);

    unsigned int addGPUUiMesh(size_t memory);
    void changeGPUUiMeshData(unsigned int meshId, unsigned int elementID, size_t offset, size_t memory, std::vector<UiVertex>& vertexData, WidgetData& widgetData);

    unsigned int addShader(const std::string& vShaderSource, const std::string& fShaderSource);
    void deleteShader(unsigned int shaderId);

    unsigned int addTexture(const unsigned char* data, unsigned int width, unsigned int height, TextureWrapMode wrapU, TextureWrapMode wrapV, TextureWrapMode wrapW, TextureFilter minFilter, TextureFilter magFilter, RGBMode rgbMode, bool mipmaps);
    void deleteTexture(unsigned int textureId);

    void changeMeshUBO(unsigned int componentId, const MeshInstanceData& data) const;
    void changeUiUBO(unsigned int elementId, const WidgetData& widgetData) const;
    void changeCameraMatrixUBO(const CameraMatrices& data) const;

    void changeDirectionalLightUBO(unsigned int componentId, const GPUDirectionalLight& light) const;
    void changePointLightUBO(unsigned int componentId, const GPUPointLight& light) const;
    void changeSpotLightUBO(unsigned int componentId, const GPUSpotLight& light) const;

    void enableWireframe(bool state);
    bool getWireframeEnabled() const;

    void generateShadowMap();

  private:
    const int SHADOW_WIDTH = 16384;
    const int SHADOW_HEIGHT = 16384;

    GLuint meshUBO;
    GLuint lightsUBO;
    GLuint uiUBO;
    GLuint cameraMatrixUBO;

    GLuint shadowFBO;
    GLuint shadowMap;

    bool wireframeEnabled = false;

    std::vector<RenderCall> commands;
    std::unordered_map<unsigned int, OpenGLMesh> meshes;
    std::unordered_map<unsigned int, OpenGLShader> shaders;
    std::unordered_map<unsigned int, OpenGLTexture> textures;

    IDAllocator meshIDAllocator = IDAllocator(1024);
    IDAllocator shaderIDAllocator = IDAllocator(1024);
    IDAllocator textureIDAllocator = IDAllocator(1024);
};