#pragma once

#include <memory>
#include <mesh.hpp>
#include <renderer.hpp>
#include <vector>

class Scene {
    public:
        Scene();
        ~Scene();
        void add(std::unique_ptr<Mesh> mesh);
        void submit();
        void load();

    private:
        std::vector<std::unique_ptr<Mesh>> worldMeshes;
};