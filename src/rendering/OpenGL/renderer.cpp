#include "rendering/OpenGL/renderer.hpp"

#include "GLFW/glfw3.h"
#include "core/assetManager.hpp"
#include "core/engine.hpp"
#include "math/vector/vector3.hpp"
#include "rendering/OpenGL/OpenGLMesh.hpp"
#include "rendering/OpenGL/OpenGLShader.hpp"
#include "rendering/OpenGL/OpenGLTexture.hpp"
#include "rendering/renderingTypes.hpp"
#include "ui/core/uiTypes.hpp"

#include <stdexcept>
#include <utility>

Renderer::Renderer() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Glad has failed to initialize!");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_STENCIL_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenBuffers(1, &meshUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, meshUBO);
    glBufferData(GL_UNIFORM_BUFFER, 512 * sizeof(MeshInstanceData), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, meshUBO);

    glGenBuffers(1, &cameraMatrixUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, cameraMatrixUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraMatrices), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, cameraMatrixUBO);

    glGenBuffers(1, &uiUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, uiUBO);
    glBufferData(GL_UNIFORM_BUFFER, 512 * sizeof(WidgetData), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, uiUBO);

    glGenBuffers(1, &lightsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
    glBufferData(GL_UNIFORM_BUFFER, 512 * sizeof(DirectionalLight) + 512 * sizeof(PointLight) + 512 * sizeof(SpotLight), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 3, lightsUBO);

    generateShadowMap();

    commands.reserve(1024);
}

Renderer::~Renderer() {
    glDeleteBuffers(1, &meshUBO);
    glDeleteBuffers(1, &cameraMatrixUBO);
    glDeleteBuffers(1, &uiUBO);
    glDeleteBuffers(1, &lightsUBO);
    glDeleteFramebuffers(1, &shadowFBO);
    glDeleteTextures(1, &shadowMap);
};

unsigned int Renderer::addGPUMesh(std::vector<Vertex>& vertexData, std::vector<unsigned int>& indices) {
    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, UV));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    unsigned int meshID = meshIDAllocator.allocate();
    OpenGLMesh mesh(VAO, VBO, EBO, indices.size());

    meshes.emplace(std::make_pair(meshID, std::move(mesh)));
    return meshID;
}

void Renderer::deleteGPUMesh(const unsigned int meshID) {
    if (meshID == 0)
        return;

    meshIDAllocator.free(meshID);
    meshes.erase(meshID);
}

unsigned int Renderer::addGPUUiMesh(const size_t memory) {
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, memory, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*) offsetof(UiVertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*) offsetof(UiVertex, UV));
    glEnableVertexAttribArray(2);

    glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(UiVertex), (void*) offsetof(UiVertex, widgetID));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    unsigned int meshID = meshIDAllocator.allocate();
    OpenGLMesh mesh(VAO, VBO, 0, memory / sizeof(UiVertex));

    meshes.emplace(std::make_pair(meshID, std::move(mesh)));
    return meshID;
}

void Renderer::changeGPUUiMeshData(const unsigned int meshID, const unsigned int elementID, const size_t offset, const size_t memory, std::vector<UiVertex>& vertexData, WidgetData& widgetData) {
    if (vertexData.size() * sizeof(UiVertex) > memory)
        throw std::runtime_error("Attempted to allocate too much memory to the GPU buffer");

    if (!meshes.contains(meshID) || elementID == 0)
        return;

    OpenGLMesh& mesh = meshes.at(meshID);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

    if (vertexData.size() * sizeof(UiVertex) < memory) {
        size_t clearSize = memory - (vertexData.size() * sizeof(UiVertex));
        std::vector<char> zeros(clearSize, 0);
        glBufferSubData(GL_ARRAY_BUFFER, offset + vertexData.size() * sizeof(UiVertex), clearSize, zeros.data());
    }
    glBufferSubData(GL_ARRAY_BUFFER, offset, vertexData.size() * sizeof(UiVertex), vertexData.data());
    changeUiUBO(elementID, widgetData);

    glBindVertexArray(0);
}

unsigned int Renderer::addShader(std::string vShaderSource, std::string fShaderSource) {
    unsigned int shaderID = shaderIDAllocator.allocate();
    OpenGLShader shader(vShaderSource.c_str(), fShaderSource.c_str());

    shaders.emplace(std::make_pair(shaderID, std::move(shader)));
    return shaderID;
}

void Renderer::deleteShader(const unsigned int shaderID) {
    if (shaderID == 0)
        return;

    shaderIDAllocator.free(shaderID);
    shaders.erase(shaderID);
}

unsigned int Renderer::addTexture(
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

    unsigned int textureID = textureIDAllocator.allocate();
    OpenGLTexture texture(data, width, height, wrapU, wrapV, wrapW, minFilter, magFilter, rgbMode, mipmaps);

    textures.emplace(std::make_pair(textureID, std::move(texture)));
    return textureID;
}

void Renderer::deleteTexture(const unsigned int textureID) {
    if (textureID == 0)
        return;

    textureIDAllocator.free(textureID);
    textures.erase(textureID);
}

void Renderer::renderQueue(RenderCall cmd) {
    commands.emplace_back(std::move(cmd));
}

void Renderer::changeMeshUBO(const unsigned int componentID, MeshInstanceData& data) {
    glBindBuffer(GL_UNIFORM_BUFFER, meshUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, componentID * sizeof(MeshInstanceData), sizeof(MeshInstanceData), &data);
}

void Renderer::changeUiUBO(const unsigned int elementID, WidgetData& widgetData) {
    glBindBuffer(GL_UNIFORM_BUFFER, uiUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, elementID * sizeof(WidgetData), sizeof(WidgetData), &widgetData);
}

void Renderer::changeCameraMatrixUBO(CameraMatrices& data) {
    glBindBuffer(GL_UNIFORM_BUFFER, cameraMatrixUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraMatrices), &data);
}

void Renderer::changeDirectionalLightUBO(const unsigned int componentId, GPUDirectionalLight& light) {
    glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, componentId * sizeof(GPUDirectionalLight), sizeof(GPUDirectionalLight), &light);
}

void Renderer::changePointLightUBO(const unsigned int componentId, GPUPointLight& light) {
    glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 512 * sizeof(GPUDirectionalLight) + componentId * sizeof(GPUPointLight), sizeof(GPUPointLight), &light);
}

void Renderer::changeSpotLightUBO(const unsigned int componentId, GPUSpotLight& light) {
    glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 512 * sizeof(GPUDirectionalLight) + 512 * sizeof(GPUPointLight) + componentId * sizeof(GPUSpotLight), sizeof(GPUSpotLight), &light);
}

void Renderer::generateShadowMap() {
    glGenFramebuffers(1, &shadowFBO);

    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float clampColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::startFrame() {
    Camera& camera = Engine::get().camera;
    Window& window = Engine::get().window;

    Mat4 view = camera.getViewMatrix();
    Mat4 projection = Mat4::projection(camera.getFOV(), (float) window.getWindowSize().x / (float) window.getWindowSize().y, camera.getNearPlane(), camera.getFarPlane());
    Mat4 viewProjection = projection * view;

    CameraMatrices matrices{viewProjection, Vector4(camera.getPosition(), 0)};
    changeCameraMatrixUBO(matrices);
}

void Renderer::endFrame() {
    AssetManager& assetManager = Engine::get().assetManager;
    Window& window = Engine::get().window;

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    Mat4 orthographicProjection = Mat4::orthographic(-40.0f, 40.0f, -40.0f, 40.0f, 0.1f, 35.0f);
    Mat4 lightView = Mat4::lookAt(20.0f * -lightCall.lightDirection.normalize(), Vector3::zero, Vector3::up);
    Mat4 lightProjection = orthographicProjection * lightView;

    unsigned int shadowShaderId = assetManager.loadShader(lightCall.vertexPath, lightCall.fragmentPath);
    if (shadowShaderId == 0)
        return;

    OpenGLShader& shadowShader = shaders.at(shadowShaderId);
    shadowShader.use();
    shadowShader.setMat4("lightProjection", lightProjection);

    for (RenderCall& cmd : commands) {
        if (cmd.meshID == 0 || !cmd.transform)
            continue;

        OpenGLMesh& mesh = meshes.at(cmd.meshID);
        shadowShader.setMat4("model", *cmd.transform);
        glBindVertexArray(mesh.VAO);

        glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, NULL);
    };

    glCullFace(GL_BACK);
    glViewport(0, 0, window.getWindowSize().x, window.getWindowSize().y);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (RenderCall& cmd : commands) {
        unsigned int shaderId = assetManager.loadShader(cmd.material.vertexPath, cmd.material.fragmentPath);
        if (cmd.meshID == 0 || shaderId == 0)
            continue;

        OpenGLMesh& mesh = meshes.at(cmd.meshID);
        OpenGLShader& shader = shaders.at(shaderId);
        shader.use();

        if (cmd.transform) {
            shader.setMat4("model", *cmd.transform);
        }

        if (cmd.meshComponentID != 0) {
            shader.setInt("componentID", cmd.meshComponentID);
        }

        shader.setMat4("lightProjection", lightProjection);
        shader.setInt("shadowMap", 0);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, shadowMap);

        glBindVertexArray(mesh.VAO);
        cmd.depthTest == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

        unsigned int albedoID = assetManager.loadTexture(cmd.material.albedo);
        if (albedoID != 0) {
            OpenGLTexture& tex = textures.at(albedoID);
            shader.setInt("albedo", 1);
            tex.bind(1);
        }

        if (mesh.EBO) {
            glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, NULL);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
        }
    }
    commands.clear();

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "GL ERROR: " << err << std::endl;
    }
}

void Renderer::enableWireframe(bool state) {
    glPolygonMode(GL_FRONT_AND_BACK, state ? GL_LINE : GL_FILL);
    wireframeEnabled = state;
}

bool Renderer::getWireframeEnabled() {
    return wireframeEnabled;
}