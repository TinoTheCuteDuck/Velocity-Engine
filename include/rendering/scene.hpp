#pragma once

#include <camera.hpp>
#include <memory>
#include <mesh.hpp>
#include <vector>

class Scene {
    public:
        Scene();
        ~Scene();
        void add(std::unique_ptr<Mesh> mesh);
        void submit();
        void generate();

    private:
        std::vector<std::unique_ptr<Mesh>> worldMeshes;
};