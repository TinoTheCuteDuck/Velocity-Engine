#include "rendering/scene.hpp"

#include "core/assetManager.hpp"
#include "core/engine.hpp"
#include "math/ray.hpp"
#include "rendering/OpenGL/renderer.hpp"
#include "rendering/renderingTypes.hpp"

#include <cfloat>

void Scene::load() {
    // unsigned int sponzaId = addEntity();
    // addMeshComponent(sponzaId, ASSETS_PATH "meshes/Sponza.obj");

    unsigned int sponzaArches = addEntity();
    addMaterialComponent(sponzaArches, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_arches.jpg");
    addTransformComponent(sponzaArches, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaArches, ASSETS_PATH "/meshes/Sponza_arches.obj");

    unsigned int sponzaBigContainers = addEntity();
    addMaterialComponent(sponzaBigContainers, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_big_containers.jpg");
    addTransformComponent(sponzaBigContainers, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaBigContainers, ASSETS_PATH "/meshes/Sponza_big_containers.obj");

    unsigned int sponzaBlueCarpet = addEntity();
    addMaterialComponent(sponzaBlueCarpet, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_blue_carpet.jpg");
    addTransformComponent(sponzaBlueCarpet, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaBlueCarpet, ASSETS_PATH "/meshes/Sponza_blue_carpet.obj");

    unsigned int sponzaBlueHangingCarpet = addEntity();
    addMaterialComponent(sponzaBlueHangingCarpet, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_blue_hanging_carpet.jpg");
    addTransformComponent(sponzaBlueHangingCarpet, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaBlueHangingCarpet, ASSETS_PATH "/meshes/Sponza_blue_hanging_carpet.obj");

    unsigned int sponzaDoors = addEntity();
    addMaterialComponent(sponzaDoors, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_doors.jpg");
    addTransformComponent(sponzaDoors, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaDoors, ASSETS_PATH "/meshes/Sponza_doors.obj");

    unsigned int sponzaFlagHolders = addEntity();
    addMaterialComponent(sponzaFlagHolders, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_flag_holders.jpg");
    addTransformComponent(sponzaFlagHolders, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaFlagHolders, ASSETS_PATH "/meshes/Sponza_flag_holders.obj");

    unsigned int sponzaFloors = addEntity();
    addMaterialComponent(sponzaFloors, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_floors.jpg");
    addTransformComponent(sponzaFloors, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaFloors, ASSETS_PATH "/meshes/Sponza_floors.obj");

    unsigned int sponzaFlowerPots = addEntity();
    addMaterialComponent(sponzaFlowerPots, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_flower_pots.jpg");
    addTransformComponent(sponzaFlowerPots, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaFlowerPots, ASSETS_PATH "/meshes/Sponza_flower_pots.obj");

    unsigned int sponzaFlowers = addEntity();
    addMaterialComponent(sponzaFlowers, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_flowers.png");
    addTransformComponent(sponzaFlowers, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaFlowers, ASSETS_PATH "/meshes/Sponza_flowers.obj");

    unsigned int sponzaFlowers2 = addEntity();
    addMaterialComponent(sponzaFlowers2, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_flowers2.png");
    addTransformComponent(sponzaFlowers2, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaFlowers2, ASSETS_PATH "/meshes/Sponza_flowers2.obj");

    unsigned int sponzaGreenCarpet = addEntity();
    addMaterialComponent(sponzaGreenCarpet, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_green_carpet.jpg");
    addTransformComponent(sponzaGreenCarpet, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaGreenCarpet, ASSETS_PATH "/meshes/Sponza_green_carpet.obj");

    unsigned int sponzaGreenHangingCarpet = addEntity();
    addMaterialComponent(sponzaGreenHangingCarpet, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_green_hanging_carpet.jpg");
    addTransformComponent(sponzaGreenHangingCarpet, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaGreenHangingCarpet, ASSETS_PATH "/meshes/Sponza_green_hanging_carpet.obj");

    unsigned int sponzaHangingLightsContainer = addEntity();
    addMaterialComponent(sponzaHangingLightsContainer, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_hanging_lights_container.jpg");
    addTransformComponent(sponzaHangingLightsContainer, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaHangingLightsContainer, ASSETS_PATH "/meshes/Sponza_hanginglights_container.obj");

    unsigned int sponzaHangingLights = addEntity();
    addMaterialComponent(sponzaHangingLights, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_hanginglights.png");
    addTransformComponent(sponzaHangingLights, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaHangingLights, ASSETS_PATH "/meshes/Sponza_hanginglights.obj");

    unsigned int sponzaLionFace = addEntity();
    addMaterialComponent(sponzaLionFace, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_lion_face.jpg");
    addTransformComponent(sponzaLionFace, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaLionFace, ASSETS_PATH "/meshes/Sponza_lion_face.obj");

    unsigned int sponzaLions = addEntity();
    addMaterialComponent(sponzaLions, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_lions.jpg");
    addTransformComponent(sponzaLions, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaLions, ASSETS_PATH "/meshes/Sponza_lions.obj");

    unsigned int sponzaPillars = addEntity();
    addMaterialComponent(sponzaPillars, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_pillars.jpg");
    addTransformComponent(sponzaPillars, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaPillars, ASSETS_PATH "/meshes/Sponza_pillars.obj");

    unsigned int sponzaRandomThing = addEntity();
    addMaterialComponent(sponzaRandomThing, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_random_thing.png");
    addTransformComponent(sponzaRandomThing, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaRandomThing, ASSETS_PATH "/meshes/Sponza_random_thing.obj");

    unsigned int sponzaRedCarpet = addEntity();
    addMaterialComponent(sponzaRedCarpet, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_red_carpet.jpg");
    addTransformComponent(sponzaRedCarpet, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaRedCarpet, ASSETS_PATH "/meshes/Sponza_red_carpet.obj");

    unsigned int sponzaRedHangingCarpet = addEntity();
    addMaterialComponent(sponzaRedHangingCarpet, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_red_hanging_carpets.jpg");
    addTransformComponent(sponzaRedHangingCarpet, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaRedHangingCarpet, ASSETS_PATH "/meshes/Sponza_red_hanging_carpet.obj");

    unsigned int sponzaRoofArches = addEntity();
    addMaterialComponent(sponzaRoofArches, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_roof_arches.jpg");
    addTransformComponent(sponzaRoofArches, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaRoofArches, ASSETS_PATH "/meshes/Sponza_roof_arches.obj");

    unsigned int sponzaRoof = addEntity();
    addMaterialComponent(sponzaRoof, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_roof.jpg");
    addTransformComponent(sponzaRoof, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaRoof, ASSETS_PATH "/meshes/Sponza_roof.obj");

    unsigned int sponzaTopPillars = addEntity();
    addMaterialComponent(sponzaTopPillars, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_top_pillars.jpg");
    addTransformComponent(sponzaTopPillars, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaTopPillars, ASSETS_PATH "/meshes/Sponza_top_pillars.obj");

    unsigned int sponzaTopSmallerPillars = addEntity();
    addMaterialComponent(sponzaTopSmallerPillars, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_top_smaller_pillars.jpg");
    addTransformComponent(sponzaTopSmallerPillars, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaTopSmallerPillars, ASSETS_PATH "/meshes/Sponza_top_smaller_pillars.obj");

    unsigned int sponzaWalls = addEntity();
    addMaterialComponent(sponzaWalls, defaultVertexShader, defaultFragmentShader, ASSETS_PATH "/textures/Sponza_walls.jpg");
    addTransformComponent(sponzaWalls, Vector3(), Vector3(0.01f));
    addMeshComponent(sponzaWalls, ASSETS_PATH "/meshes/Sponza_walls.obj");

    // unsigned int floorId = addEntity();
    // addMeshComponent(floorId, ASSETS_PATH "meshes/Plane.obj");

    // unsigned int blockId = addEntity();
    // addTransformComponent(blockId, Vector3(0, 4, 0), Vector3(0.01, 1, 0.01));
    // addMeshComponent(blockId, ASSETS_PATH "meshes/Plane.obj");

    unsigned int directionalLight = addEntity();
    addDirectionalLightComponent(directionalLight, Vector3(-0.2f, -0.8f, 0.2f).normalize(), Vector3(1.0f, 0.92f, 0.75f), 1);
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
    unsigned int componentID = meshComponentIDAllocator.allocate();

    Engine::get().assetManager.loadMesh(filePath);
    MeshInstance mesh(filePath, componentID);

    meshes.emplace(entity, std::move(mesh));

    if (!transforms.contains(entity)) {
        addTransformComponent(entity);
    }
    if (!materials.contains(entity)) {
        addMaterialComponent(entity);
    }
}
void Scene::removeMeshComponent(unsigned int entity) {
    meshComponentIDAllocator.free(meshes.at(entity).componentID);
    meshes.erase(entity);
}

void Scene::addRigidBodyComponent(unsigned int entity, const RigidBody&& body) {
    rigidBodys.emplace(entity, std::move(body));
}
void Scene::removeRigidBodyComponent(unsigned int entity) {
    rigidBodys.erase(entity);
}

void Scene::addMaterialComponent(unsigned int entity, const std::string& vertexPath, const std::string& fragmentPath, const std::string& albedo) {
    std::string vertexShader = vertexPath != "" ? vertexPath : defaultVertexShader;
    std::string fragmentShader = fragmentPath != "" ? fragmentPath : defaultFragmentShader;
    std::string albedoMap = albedo != "" ? albedo : defaultAlbedo;

    Engine::get().assetManager.loadTexture(albedoMap);

    Material material = {vertexShader, fragmentShader, albedoMap};
    materials.emplace(std::make_pair(entity, std::move(material)));
}
void Scene::removeMaterialComponent(unsigned int entity) {
    materials.erase(entity);
}

void Scene::addDirectionalLightComponent(unsigned int entity, const Vector3& direction, const Vector3& color, const float intensity) {
    unsigned int componentId = directionalLightComponentIDAllocator.allocate();

    DirectionalLight light = {componentId, direction, color, intensity};
    directionalLights.emplace(std::make_pair(entity, std::move(light)));
}
void Scene::removeDirectionalLightComponent(unsigned int entity) {
    directionalLights.erase(entity);
}

void Scene::addPointLightComponent(unsigned int entity, const Vector3& position, const Vector3& color, const float intensity, const float constant, const float linear, const float quadratic) {
    unsigned int componentId = pointLightComponentIDAllocator.allocate();

    PointLight light = {componentId, position, color, intensity, constant, linear, quadratic};
    pointLights.emplace(std::make_pair(entity, std::move(light)));
}
void Scene::removePointLightComponent(unsigned int entity) {
    pointLights.erase(entity);
}

void Scene::addSpotLightComponent(unsigned int entity, const Vector3& position, const Vector3& direction, const Vector3& color, const float intensity, const float outerAngle, const float innerAngle, const float constant, const float linear, const float quadratic) {
    unsigned int componentId = spotLightComponentIDAllocator.allocate();

    SpotLight light = {componentId, position, direction, color, intensity, outerAngle, innerAngle, constant, linear, quadratic};
    spotLights.emplace(std::make_pair(entity, std::move(light)));
}
void Scene::removeSpotLightComponent(unsigned int entity) {
    spotLights.erase(entity);
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
    removeMaterialComponent(entity);
    removeDirectionalLightComponent(entity);
    removePointLightComponent(entity);
    removeSpotLightComponent(entity);
}

void Scene::submit() {
    Renderer& renderer = Engine::get().renderer;
    AssetManager& assetManager = Engine::get().assetManager;

    for (auto& [id, component] : directionalLights) {
        renderer.lightCall = LightRenderCall{
            component.direction.get(),
            defaultShadowVertexShader,
            defaultShadowFragmentShader};
    }

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
            component.componentID,
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