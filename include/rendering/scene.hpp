#pragma once

#include <camera.hpp>
#include <memory>
#include <mesh.hpp>
#include <renderer.hpp>
#include <shader.hpp>
#include <vector>

class Scene {
    public:
        Scene();
        ~Scene();
        void add(std::unique_ptr<Mesh> mesh);
        void submit(Renderer& renderer, Shader& sceneShader);
        void generate();

    private:
        std::vector<std::unique_ptr<Mesh>> worldMeshes;
};