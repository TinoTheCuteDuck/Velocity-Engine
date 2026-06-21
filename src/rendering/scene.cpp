#include "rendering/scene.hpp"

#include "core/assetManager.hpp"
#include "core/engine.hpp"
#include "math/ray.hpp"
#include "rendering/OpenGL/renderer.hpp"

#include <cfloat>

void Scene::load() {
    // unsigned int bunnyId = addEntity();
    // addMeshComponent(bunnyId, Mesh(ASSETS_PATH "meshes/stanford-bunny.obj"));
    // addTransformComponent(bunnyId, Transform{Vector3(0, 50, 0), Vector3(20), Vector3()});
    // addRigidBodyComponent(bunnyId, RigidBody());

    // unsigned int bunnyId2 = addEntity();
    // addMeshComponent(bunnyId2, Mesh(ASSETS_PATH "meshes/stanford-bunny.obj"));
    // addTransformComponent(bunnyId2, Transform{Vector3(0, 100, 0), Vector3(20), Vector3()});
    // addRigidBodyComponent(bunnyId2, RigidBody());

    unsigned int planeId = addEntity();
    addMeshComponent(planeId, ASSETS_PATH "meshes/Plane.obj");
}

void Scene::update() {
    AssetManager& assetManager = Engine::get().assetManager;

    // if (!Engine::get().uiManager.uiFocus) {
    //     pickObject(Engine::get().camera.screenPointToRay(Engine::get().input.getMousePos()));
    // }

    // Physics update
    for (auto& [id, component] : rigidBodys) {
        if (transforms.contains(id)) {
            component.update(transforms.at(id));
        }
    }

    // Collision update
    for (auto& [id, component] : meshes) {
        if (transforms.count(id) && rigidBodys.count(id)) {
            MeshData* meshData = assetManager.getMesh(component.filePath);
            if (!meshData || meshData->meshId == 0)
                continue;

            Transform& transform = transforms.at(id);
            BoundingBox bounds = meshData->boundingBox;
            Mat4 matrix = transform.getMatrice();
            Vector4 min = matrix * Vector4(bounds.min, 1);
            Vector4 max = matrix * Vector4(bounds.max, 1);
            bounds.min = Vector3(min.x, min.y, min.z);
            bounds.max = Vector3(max.x, max.y, max.z);

            for (auto& [iterationID, iterationComponent] : meshes) {
                if (id == iterationID)
                    continue;

                MeshData* iterationMeshData = assetManager.getMesh(iterationComponent.filePath);
                if (!iterationMeshData || iterationMeshData->meshId == 0)
                    continue;

                Transform& transform = transforms.at(iterationID);
                BoundingBox iterationBounds = iterationMeshData->boundingBox;
                Mat4 matrix = transform.getMatrice();
                Vector4 min = matrix * Vector4(iterationBounds.min, 1);
                Vector4 max = matrix * Vector4(iterationBounds.max, 1);
                iterationBounds.min = Vector3(min.x, min.y, min.z);
                iterationBounds.max = Vector3(max.x, max.y, max.z);

                bool minX = bounds.min.x < iterationBounds.max.x;
                bool minY = bounds.min.y < iterationBounds.max.y;
                bool minZ = bounds.min.z < iterationBounds.max.z;

                bool maxX = bounds.max.x > iterationBounds.min.x;
                bool maxY = bounds.max.y > iterationBounds.min.y;
                bool maxZ = bounds.max.z > iterationBounds.min.z;

                if (minX && minY && minZ && maxX && maxY && maxZ) {
                    rigidBodys.at(id).velocity *= -0.6f;
                    if (rigidBodys.count(iterationID)) {
                        rigidBodys.at(iterationID).velocity *= -0.6f;
                    }
                }
            }
        }
    }
}

void Scene::addTransformComponent(unsigned int entity, Vector3 position, Vector3 scale, Vector3 rotation) {
    Transform transform(position, scale, rotation);
    transforms.emplace(entity, std::move(transform));
}
void Scene::removeTransformComponent(unsigned int entity) {
    transforms.erase(entity);
}

void Scene::addMeshComponent(unsigned int entity, const std::string& filePath) {
    Engine::get().assetManager.loadMesh(filePath);
    MeshInstance mesh(filePath);

    meshes.emplace(entity, std::move(mesh));

    if (!transforms.contains(entity)) {
        addTransformComponent(entity);
    }
    if (!materials.contains(entity)) {
        Material material{ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag", {}};
        materials.emplace(std::make_pair(entity, std::move(material)));
    }
}
void Scene::removeMeshComponent(unsigned int entity) {
    meshes.erase(entity);
}

void Scene::addRigidBodyComponent(unsigned int entity, const RigidBody&& body) {
    rigidBodys.emplace(entity, std::move(body));
}
void Scene::removeRigidBodyComponent(unsigned int entity) {
    rigidBodys.erase(entity);
}

unsigned int Scene::addEntity() {
    unsigned int entityID = entityIDAllocator.allocate();
    entities.emplace(entityID, entityID);
    return entityID;
}
void Scene::removeEntity(unsigned int entity) {
    entityIDAllocator.free(entity);
    entities.erase(entity);
    removeTransformComponent(entity);
    removeMeshComponent(entity);
    removeRigidBodyComponent(entity);
}

void Scene::submit() {
    Renderer& renderer = Engine::get().renderer;
    AssetManager& assetManager = Engine::get().assetManager;

    for (auto& [id, component] : meshes) {
        if (!transforms.contains(id) || !materials.contains(id)) {
            std::cout << "Mesh does not contain a transform or material!" << std::endl;
            continue;
        }

        MeshData* meshData = assetManager.getMesh(component.filePath);
        if (!meshData || meshData->meshId == 0)
            continue;

        unsigned int meshId = meshData->meshId;
        Material& material = materials.at(id);

        renderer.renderQueue(RenderCall{
            meshId,
            material,
            transforms.at(id).getMatrice(),
            true});
    }
}

void Scene::pickObject(const Ray ray) {
    AssetManager& assetManager = Engine::get().assetManager;

    float closestT = FLT_MAX;
    unsigned int closestEntity = 0;

    for (auto& [id, component] : meshes) {
        float t0x, t1x, t0y, t1y, t0z, t1z;

        MeshData* meshData = assetManager.getMesh(component.filePath);
        if (!meshData || meshData->meshId == 0)
            continue;

        BoundingBox bounds = meshData->boundingBox;
        if (!transforms.count(id)) {
            std::cout << "Mesh does not have a transform!" << std::endl;
            continue;
        }

        Mat4 model = transforms.at(id).getMatrice();
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
            closestEntity = id;
        }
    }
    if (Engine::get().input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        if (closestEntity > 0) {
            selectedEntity = closestEntity;
        } else {
            selectedEntity = 0;
        }
    }
}

void Scene::setSelectedEntity(unsigned int id) {
    selectedEntity = id;
}

unsigned int Scene::getSelectedEntity() {
    return selectedEntity;
}