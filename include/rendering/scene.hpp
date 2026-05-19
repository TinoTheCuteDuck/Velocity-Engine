#pragma once

#include <core/input.hpp>
#include <math/ray.hpp>
#include <physics/rigidBody.hpp>
#include <rendering/camera.hpp>
#include <rendering/mesh.hpp>

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
        void add(std::shared_ptr<GameObject> gameObject);
        void update();
        void submit();
        void load();

        std::shared_ptr<GameObject> getSelectedObject();

    private:
        void pickObject(const Ray ray);
        std::vector<std::shared_ptr<GameObject>> gameObjects;
        std::shared_ptr<GameObject> selectedObject;
};