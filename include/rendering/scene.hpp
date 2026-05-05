#pragma once

#include <camera.hpp>
#include <input.hpp>
#include <mesh.hpp>
#include <rigidBody.hpp>

#include <memory>
#include <vector>

struct GameObject {
        std::unique_ptr<Mesh> mesh;
        std::unique_ptr<RigidBody> body;

        GameObject(std::unique_ptr<Mesh> m, std::unique_ptr<RigidBody> b) : mesh(std::move(m)), body(std::move(b)) {}

        void update() {
            if (body) {
                body->update();
                mesh->position = body->position;
            }
        }
};

class Scene {
    public:
        Scene();
        void add(std::unique_ptr<GameObject> gameObject);
        void update();
        void submit();
        void load();

    private:
        std::vector<std::unique_ptr<GameObject>> gameObjects;
};