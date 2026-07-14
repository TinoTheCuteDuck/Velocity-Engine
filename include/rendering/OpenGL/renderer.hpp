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
    void startFrame();
    void endFrame();

    unsigned int addGPUMesh(std::vector<Vertex>& vertexData, std::vector<unsigned int>& indices);
    void deleteGPUMesh(const unsigned int meshId);

    unsigned int addGPUUiMesh(const size_t memory);
    void changeGPUUiMeshData(const unsigned int meshId, const unsigned int elementID, const size_t offset, const size_t memory, std::vector<UiVertex>& vertexData, WidgetData& widgetData);

    unsigned int addShader(std::string vShaderSource, std::string fShaderSource);
    void deleteShader(const unsigned int shaderId);

    unsigned int addTexture(unsigned char* data, unsigned int width, unsigned int height, TextureWrapMode wrapU, TextureWrapMode wrapV, TextureWrapMode wrapW, TextureFilter minFilter, TextureFilter magFilter, RGBMode rgbMode, bool mipmaps);
    void deleteTexture(const unsigned int textureId);

    void changeMeshUBO(const unsigned int componentId, MeshInstanceData& data);
    void changeUiUBO(const unsigned int elementId, WidgetData& widgetData);
    void changeCameraMatrixUBO(CameraMatrices& data);

    void changeDirectionalLightUBO(const unsigned int componentId, GPUDirectionalLight& light);
    void changePointLightUBO(const unsigned int componentId, GPUPointLight& light);
    void changeSpotLightUBO(const unsigned int componentId, GPUSpotLight& light);

    void enableWireframe(bool state);
    bool getWireframeEnabled();

    void generateShadowMap();

  private:
    const int SHADOW_WIDTH = 4096;
    const int SHADOW_HEIGHT = 4096;

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