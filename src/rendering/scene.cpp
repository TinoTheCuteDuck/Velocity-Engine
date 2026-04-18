#include <engineContext.hpp>
#include <memory>
#include <renderer.hpp>
#include <scene.hpp>

Scene::Scene() {
    add(std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj"));
}

Scene::~Scene() {
}

void Scene::add(std::unique_ptr<Mesh> mesh) {
    worldMeshes.push_back(std::move(mesh));
}

void Scene::submit() {
    for (std::unique_ptr<Mesh>& mesh : worldMeshes) {
        gEngineContext.renderer->renderQueue(RenderCall{
            gEngineContext.sceneShader,
            mesh->VAO,
            GL_TRIANGLES,
            GL_UNSIGNED_INT,
            mesh->indicesCount,
            true,
            mesh->modelMatrice()});
    }
}