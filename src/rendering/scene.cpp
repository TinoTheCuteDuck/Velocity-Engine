#include <rendering/scene.hpp>

#include <core/engine.hpp>

#include <rendering/OpenGL/renderer.hpp>
#include <rendering/mesh.hpp>

#include <physics/rigidBody.hpp>

#include <cfloat>
#include <memory>
#include <vector>

Scene::Scene() {
}

void Scene::load() {
    add(std::make_shared<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/stanford-bunny.obj", Vector3(0, 20, 0), Vector3(20)),
        std::make_unique<RigidBody>(Vector3(0, 20, 0))));
    add(std::make_shared<GameObject>(
        std::make_unique<Mesh>(ASSETS_PATH "meshes/Plane.obj", Vector3(), Vector3(1)),
        nullptr));
}

void Scene::update() {
    pickObject(Engine::get().camera.screenPointToRay(Engine::get().input.getMousePos()));
    for (std::shared_ptr<GameObject>& obj : gameObjects) {
        obj->update();
    }
}

void Scene::add(std::shared_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

void Scene::submit() {
    Renderer& renderer = Engine::get().renderer;
    for (std::shared_ptr<GameObject>& obj : gameObjects) {
        renderer.renderQueue(RenderCall{
            obj->mesh->meshID,
            obj->mesh->material,
            obj->mesh->modelMatrice(),
            true});
    }
}

void Scene::pickObject(const Ray ray) {
    float closestT = FLT_MAX;
    std::shared_ptr<GameObject> closestObject = nullptr;

    for (std::shared_ptr<GameObject>& obj : gameObjects) {
        float t0x, t1x, t0y, t1y, t0z, t1z;

        BoundingBox bounds = obj->mesh->boundingBox;
        Mat4 model = obj->mesh->modelMatrice();
        Vector4 min = model * Vector4(bounds.min, 1.0f);
        Vector4 max = model * Vector4(bounds.max, 1.0f);
        bounds.min = Vector3(min.x, min.y, min.z);
        bounds.max = Vector3(max.x, max.y, max.z);

        t0x = (bounds[ray.sign[0]].x - ray.origin.x) * ray.invDirection.x;
        t1x = (bounds[1 - ray.sign[0]].x - ray.origin.x) * ray.invDirection.x;

        t0y = (bounds[ray.sign[1]].y - ray.origin.y) * ray.invDirection.y;
        t1y = (bounds[1 - ray.sign[1]].y - ray.origin.y) * ray.invDirection.y;

        if ((t0x > t1x) || (t0y > t1y)) {
            continue;
        }

        if (t0y > t0x) {
            t0x = t0y;
        }
        if (t1y < t1x) {
            t1x = t1y;
        }

        t0z = (bounds[ray.sign[2]].z - ray.origin.z) * ray.invDirection.z;
        t1z = (bounds[1 - ray.sign[2]].z - ray.origin.z) * ray.invDirection.z;

        if ((t0x > t1z) || (t0z > t1x)) {
            continue;
        }

        if (t0z > t0x) {
            t0x = t0z;
        }
        if (t1z < t1x) {
            t1x = t1z;
        }

        if (t0x < closestT && t0x > 0) {
            closestT = t0x;
            closestObject = obj;
        }
    }
    if (closestObject) {
        if (Engine::get().input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            selectedObject = closestObject;
            std::cout << "Selected ID: " << selectedObject->mesh->meshID << std::endl;
        }
    }
}

std::shared_ptr<GameObject> Scene::getSelectedObject() {
    return selectedObject;
}