#include <memory>
#include <mesh.hpp>
#include <renderer.hpp>
#include <scene.hpp>

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::load() {
    add(std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj"));
}

void Scene::add(std::unique_ptr<Mesh> mesh) {
    worldMeshes.push_back(std::move(mesh));
}

void Scene::submit() {
    Renderer& renderer = Renderer::get();
    for (std::unique_ptr<Mesh>& mesh : worldMeshes) {
        renderer.renderQueue(RenderCall{
            mesh->meshID,
            mesh->material,
            mesh->modelMatrice()});
    }
}