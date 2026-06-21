#include "rendering/OpenGL/renderer.hpp"

#include "GLFW/glfw3.h"
#include "core/assetManager.hpp"
#include "core/engine.hpp"
#include "rendering/OpenGL/OpenGLMesh.hpp"
#include "rendering/OpenGL/OpenGLShader.hpp"
#include "rendering/OpenGL/OpenGLTexture.hpp"
#include "rendering/meshData.hpp"
#include "ui/core/uiStructs.hpp"

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

    commands.reserve(1024);
}

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

    unsigned int meshId = meshIdAllocator.allocate();
    OpenGLMesh mesh(VAO, VBO, EBO, 0, vertexData.size());

    meshes.emplace(std::make_pair(meshId, std::move(mesh)));
    return meshId;
}

void Renderer::deleteGPUMesh(const unsigned int meshID) {
    if (meshID == 0)
        return;

    meshIdAllocator.free(meshID);
    meshes.erase(meshID);
}

unsigned int Renderer::addGPUUiMesh(const size_t memory) {
    unsigned int VAO, VBO, UBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, memory, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, 512 * sizeof(WidgetData), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, UBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*) offsetof(UiVertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*) offsetof(UiVertex, UV));
    glEnableVertexAttribArray(2);

    glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(UiVertex), (void*) offsetof(UiVertex, widgetID));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    unsigned int meshId = meshIdAllocator.allocate();
    OpenGLMesh mesh(VAO, VBO, 0, UBO, memory / sizeof(UiVertex));

    meshes.emplace(std::make_pair(meshId, std::move(mesh)));
    return meshId;
}

void Renderer::changeGPUUiMeshData(const unsigned int meshID, const unsigned int elementID, const size_t offset, const size_t memory, std::vector<UiVertex>& vertexData, WidgetData& widgetData) {
    if (vertexData.size() * sizeof(UiVertex) > memory)
        throw std::runtime_error("Attempted to allocate too much memory to the GPU buffer");

    if (!meshes.contains(meshID))
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

    glBindBuffer(GL_UNIFORM_BUFFER, mesh.UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, elementID * sizeof(WidgetData), sizeof(WidgetData), &widgetData);

    glBindVertexArray(0);
}

unsigned int Renderer::addShader(std::string vShaderSource, std::string fShaderSource) {
    unsigned int shaderId = shaderIDAllocator.allocate();
    OpenGLShader shader(vShaderSource.c_str(), fShaderSource.c_str());

    shaders.emplace(std::make_pair(shaderId, std::move(shader)));
    return shaderId;
}

void Renderer::deleteShader(const unsigned int shaderID) {
    if (shaderID)
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

    unsigned int textureId = textureIDAllocator.allocate();
    OpenGLTexture texture(data, width, height, wrapU, wrapV, wrapW, minFilter, magFilter, rgbMode, mipmaps);

    textures.emplace(std::make_pair(textureId, std::move(texture)));
    return textureId;
}

void Renderer::deleteTexture(const unsigned int textureID) {
    if (textureID)
        return;

    textureIDAllocator.free(textureID);
    textures.erase(textureID);
}

void Renderer::renderQueue(RenderCall cmd) {
    commands.emplace_back(std::move(cmd));
}

void Renderer::startFrame() {
    Camera& camera = Engine::get().camera;
    Window& window = Engine::get().window;
    AssetManager& assetManager = Engine::get().assetManager;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    unsigned int shaderId = assetManager.loadShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag");
    if (shaderId == 0)
        return;

    OpenGLShader& shader = shaders.at(shaderId);
    shader.use();

    Mat4 projection = Mat4::projection(camera.getFOV(), (float) window.getWindowSize().x / (float) window.getWindowSize().y, camera.getNearPlane(), camera.getFarPlane());
    shader.setMat4("projection", projection);
    shader.setMat4("view", camera.getViewMatrix());
}

void Renderer::endFrame() {
    AssetManager& assetManager = Engine::get().assetManager;

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

        glBindVertexArray(mesh.VAO);
        cmd.depthTest == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

        int texCount = 0;
        for (auto& [name, texturePath] : cmd.material.textures) {
            unsigned int textureId = assetManager.loadTexture(texturePath);

            if (textureId != 0) {
                OpenGLTexture& tex = textures.at(textureId);
                shader.setInt(name, texCount);
                tex.bind(texCount++);
            }
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