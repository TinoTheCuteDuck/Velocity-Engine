#include "texture.hpp"
#include <engineState.hpp>
#include <mesh.hpp>
#include <renderer.hpp>
#include <ressources.hpp>
#include <shader.hpp>
#include <stdexcept>
#include <tuple>
#include <uiElement.hpp>
#include <utility>

Renderer::Renderer() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    commands.reserve(1024);
}

Renderer& Renderer::get() {
    if (!instance) {
        throw std::runtime_error("Renderer not initialized!");
    }
    return *instance;
}

void Renderer::setInstance(Renderer& renderer) {
    instance = &renderer;
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

    meshes.emplace(std::make_pair(currentMeshID, GPUMesh{VAO, VBO, EBO, indices.size()}));
    return currentMeshID++;
}

void Renderer::deleteGPUMesh(const unsigned int meshID) {
    GPUMesh& mesh = meshes.at(meshID);
    glDeleteVertexArrays(1, &mesh.VAO);
    glDeleteBuffers(1, &mesh.VBO);
    glDeleteBuffers(1, &mesh.EBO);
    meshes.erase(meshID);
}

void Renderer::changeGPUMeshData(const unsigned int meshID, const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indices) {
    GPUMesh& mesh = meshes.at(meshID);
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

unsigned int Renderer::addGPUUiMesh(const std::vector<UiVertex>& vertexData) {
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UiVertex) * vertexData.size(), vertexData.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)offsetof(UiVertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UiVertex), (void*)offsetof(UiVertex, UV));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    meshes.emplace(std::make_pair(currentMeshID, GPUMesh{VAO, VBO, 0, vertexData.size()}));
    return currentMeshID++;
}

void Renderer::deleteGPUUiMesh(const unsigned int meshID) {
    GPUMesh& mesh = meshes.at(meshID);
    glDeleteVertexArrays(1, &mesh.VAO);
    glDeleteBuffers(1, &mesh.VBO);
    meshes.erase(meshID);
}

void Renderer::changeGPUUiMeshData(const unsigned int meshID, const std::vector<UiVertex>& vertexData) {
    GPUMesh& mesh = meshes.at(meshID);
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UiVertex) * vertexData.size(), vertexData.data(), GL_DYNAMIC_DRAW);

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

void Renderer::startFrame(Camera& camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader& shader = shaders.at(Ressources::pbrShader);
    shader.use();

    Mat4 projection = Mat4::projection(EngineState::settings.FOV, (float)EngineState::viewport.width / (float)EngineState::viewport.height, EngineState::settings.nearPlane, EngineState::settings.farPlane);
    shader.setMat4("projection", projection);
    shader.setMat4("view", camera.getViewMatrix());
}

void Renderer::endFrame() {
    for (RenderCall& cmd : commands) {
        Shader& shader = shaders.at(cmd.material.shaderID);
        shader.use();

        if (cmd.transform) {
            shader.setMat4("model", *cmd.transform);
        }

        glBindVertexArray(meshes.at(cmd.meshID).VAO);
        unsigned int count = meshes.at(cmd.meshID).vertexCount;

        int texCount = 0;
        for (auto& [name, texID] : cmd.material.textures) {
            Texture& tex = textures.at(texID);
            shader.setInt(name, texCount);
            tex.bind(texCount);
            texCount++;
        }

        if (meshes.at(cmd.meshID).EBO) {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, count);
        }
    }
    commands.clear();

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "GL ERROR: " << err << std::endl;
    }
}