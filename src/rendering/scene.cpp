#include <memory>
#include <mesh.hpp>
#include <renderer.hpp>
#include <scene.hpp>
#include <shader.hpp>

Scene::Scene() {
    add(std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj"));
}

Scene::~Scene() {
}

void Scene::add(std::unique_ptr<Mesh> mesh) {
    worldMeshes.push_back(std::move(mesh));
}

void Scene::submit(Renderer& renderer, Shader& sceneShader) {
    for (std::unique_ptr<Mesh>& mesh : worldMeshes) {
        renderer.renderQueue(RenderCall{
            &sceneShader,
            mesh->VAO,
            GL_TRIANGLES,
            GL_UNSIGNED_INT,
            mesh->indicesCount,
            true,
            mesh->modelMatrice()});
    }
}