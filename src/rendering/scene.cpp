#include <scene.hpp>

#include <mesh.hpp>
#include <renderer.hpp>
#include <rigidBody.hpp>

#include <memory>
#include <vector>

Scene::Scene() {
}

void Scene::load() {
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj", Vector3(0, 100, 0), 20),
        std::make_unique<RigidBody>(Vector3(0, 100, 0))));
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj", Vector3(10, 80, 0), 20),
        std::make_unique<RigidBody>(Vector3(10, 80, 0))));
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj", Vector3(20, 60, 0), 20),
        std::make_unique<RigidBody>(Vector3(20, 60, 0))));
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj", Vector3(30, 40, 0), 20),
        std::make_unique<RigidBody>(Vector3(30, 40, 0))));
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj", Vector3(40, 20, 0), 20),
        std::make_unique<RigidBody>(Vector3(40, 20, 0))));
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/Plane.obj", Vector3(), 1),
        nullptr));
}

void Scene::update() {
    for (std::unique_ptr<GameObject>& obj : gameObjects) {
        obj->update();
    }
}

void Scene::add(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

void Scene::submit() {
    Renderer& renderer = Renderer::get();
    for (std::unique_ptr<GameObject>& obj : gameObjects) {
        renderer.renderQueue(RenderCall{
            obj->mesh->meshID,
            obj->mesh->material,
            obj->mesh->modelMatrice()});
    }
}