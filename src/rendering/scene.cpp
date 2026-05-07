#include <scene.hpp>

#include <engine.hpp>
#include <mesh.hpp>
#include <renderer.hpp>
#include <rigidBody.hpp>

#include <memory>
#include <vector>

Scene::Scene() {
}

void Scene::load() {
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj", Vector3(0, 20, 0), 20),
        std::make_unique<RigidBody>(Vector3(0, 20, 0))));
    add(std::make_unique<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/Plane.obj", Vector3(), 1),
        nullptr));
}

void Scene::update() {
    pickObject(Engine::get().camera.screenPointToRay(Engine::get().input.getMousePos(), 100.0f));
    for (std::unique_ptr<GameObject>& obj : gameObjects) {
        obj->update();
    }
}

void Scene::add(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

void Scene::submit() {
    Renderer& renderer = Engine::get().renderer;
    for (std::unique_ptr<GameObject>& obj : gameObjects) {
        renderer.renderQueue(RenderCall{
            obj->mesh->meshID,
            obj->mesh->material,
            obj->mesh->modelMatrice()});
    }
}

void Scene::pickObject([[maybe_unused]] const Ray ray) {
}