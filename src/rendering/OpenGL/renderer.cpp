#include <rendering/OpenGL/renderer.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <core/engine.hpp>
#include <core/ressources.hpp>

#include <rendering/OpenGL/shader.hpp>
#include <rendering/OpenGL/texture.hpp>
#include <rendering/mesh.hpp>

#include <ui/uiWidget.hpp>

#include <stdexcept>
#include <tuple>
#include <utility>

Renderer::Renderer() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Glad has failed to initialize!");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    commands.reserve(1024);
}

unsigned int Renderer::addGPUMesh(const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indices) {
    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    meshes.emplace(std::piecewise_construct, std::forward_as_tuple(currentMeshID), std::forward_as_tuple(VAO, VBO, EBO, 0, indices.size()));
    return currentMeshID++;
}

void Renderer::deleteGPUMesh(const unsigned int meshID) {
    meshes.erase(meshID);
}

void Renderer::changeGPUVertexCount(const unsigned int meshID, const size_t vertexCount) {
    meshes.at(meshID).vertexCount = vertexCount;
}

void Renderer::changeGPUMeshData(const unsigned int meshID, const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indices) {
    GPUMesh& mesh = meshes.at(meshID);
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    mesh.vertexCount = indices.size();

    glBindVertexArray(0);
}

unsigned int Renderer::addGPUUiMesh(const size_t memory, const unsigned int elementID) {
    unsigned int VAO, VBO, UBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, memory, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, elementID * sizeof(WidgetData), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, UBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)offsetof(UiVertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)offsetof(UiVertex, UV));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(UiVertex), (void*)offsetof(UiVertex, widgetID));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    meshes.emplace(std::piecewise_construct, std::forward_as_tuple(currentMeshID), std::forward_as_tuple(VAO, VBO, 0, UBO, 0));
    return currentMeshID++;
}

void Renderer::changeGPUUiMeshData(const unsigned int meshID, const unsigned int elementID, const size_t offset, const size_t memory, const std::vector<UiVertex>& vertexData, WidgetData& widgetData) {
    if (vertexData.size() * sizeof(UiVertex) > memory)
        throw std::runtime_error("Attempted to allocate too much memory to the GPU buffer");

    GPUMesh& mesh = meshes.at(meshID);
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, offset, vertexData.size() * sizeof(UiVertex), vertexData.data());

    glBindBuffer(GL_UNIFORM_BUFFER, mesh.UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, elementID * sizeof(WidgetData), sizeof(WidgetData), &widgetData);

    glBindVertexArray(0);
}

unsigned int Renderer::addShader(const std::string& vertexPath, const std::string& fragmentPath) {
    shaders.emplace(std::piecewise_construct, std::forward_as_tuple(currentShaderID), std::forward_as_tuple(vertexPath, fragmentPath));
    return currentShaderID++;
}

void Renderer::deleteShader(const unsigned int shaderID) {
    shaders.erase(shaderID);
}

unsigned int Renderer::addTexture(const std::string& filepath, GLenum wrapMode, GLenum filterMode, bool generateMipmaps) {
    textures.emplace(std::piecewise_construct, std::forward_as_tuple(currentTextureID), std::forward_as_tuple(filepath, wrapMode, filterMode, generateMipmaps));
    return currentTextureID++;
}

void Renderer::deleteTexture(const unsigned int textureID) {
    textures.erase(textureID);
}

void Renderer::renderQueue(RenderCall cmd) {
    commands.emplace_back(std::move(cmd));
}

void Renderer::startFrame() {
    Camera& camera = Engine::get().camera;
    Window& window = Engine::get().window;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader& shader = shaders.at(Ressources::pbrShader);
    shader.use();

    Mat4 projection = Mat4::projection(camera.getFOV(), (float)window.getWindowSize().x / (float)window.getWindowSize().y, camera.getNearPlane(), camera.getFarPlane());
    shader.setMat4("projection", projection);
    shader.setMat4("view", camera.getViewMatrix());
}

void Renderer::endFrame() {
    for (RenderCall& cmd : commands) {
        GPUMesh& mesh = meshes.at(cmd.meshID);
        Shader& shader = shaders.at(cmd.material.shaderID);
        shader.use();

        if (cmd.transform) {
            shader.setMat4("model", *cmd.transform);
        }

        glBindVertexArray(mesh.VAO);

        int texCount = 0;
        for (auto& [name, texID] : cmd.material.textures) {
            Texture& tex = textures.at(texID);
            shader.setInt(name, texCount);
            tex.bind(texCount++);
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