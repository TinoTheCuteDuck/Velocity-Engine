#pragma once

#include <camera.hpp>
#include <glad/glad.h>
#include <material.hpp>
#include <optional>
#include <shader.hpp>
#include <texture.hpp>
#include <uiElement.hpp>
#include <unordered_map>
#include <vector>

struct RenderCall {
        unsigned int meshID;
        Material& material;
        std::optional<Mat4> transform;
};

struct GPUMesh {
        unsigned int VAO, VBO, EBO;
        size_t vertexCount;
};

struct Vertex;

class Renderer {
    public:
        static Renderer& get();
        static void setInstance(Renderer& renderer);

        Renderer();
        void renderQueue(RenderCall cmd);
        void startFrame(Camera& camera);
        void endFrame();

        unsigned int addGPUMesh(const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indices);
        void deleteGPUMesh(const unsigned int meshID);
        void changeGPUMeshData(const unsigned int meshID, const std::vector<Vertex>& vertexData, const std::vector<unsigned int>& indices);

        unsigned int addGPUUiMesh(const std::vector<UiVertex>& vertexData);
        void deleteGPUUiMesh(const unsigned int meshID);
        void changeGPUUiMeshData(const unsigned int meshID, const std::vector<UiVertex>& vertexData);

        unsigned int addShader(const std::string& vertexPath, const std::string& fragmentPath);
        void deleteShader(const unsigned int shaderID);

        unsigned int addTexture(const std::string& filepath, GLenum wrapMode, GLenum filterMode, bool generateMipmaps);
        void deleteTexture(const unsigned int textureID);

    private:
        inline static Renderer* instance = nullptr;
        std::vector<RenderCall> commands;
        std::unordered_map<unsigned int, GPUMesh> meshes;
        std::unordered_map<unsigned int, Shader> shaders;
        std::unordered_map<unsigned int, Texture> textures;

        unsigned int currentMeshID = 1;
        unsigned int currentShaderID = 1;
        unsigned int currentTextureID = 1;
};