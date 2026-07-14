#pragma once

#include "core/idAllocator.hpp"
#include "physics/rigidBody.hpp"
#include "rendering/meshInstance.hpp"
#include "rendering/sceneTypes.hpp"

#include <unordered_map>

struct Ray;

class Scene {
  public:
    void load();
    void update();
    void submit();

    void addTransformComponent(unsigned int entity, Vector3 position = Vector3(), Vector3 scale = Vector3(1), Vector3 rotation = Vector3(0));
    void removeTransformComponent(const unsigned int entity);

    void addMeshComponent(unsigned int entity, const std::string& filePath);
    void removeMeshComponent(unsigned int entity);

    void addRigidBodyComponent(unsigned int entity, const RigidBody&& body);
    void removeRigidBodyComponent(unsigned int entity);

    void addMaterialComponent(unsigned int entity, const std::string& vertexPath = "", const std::string& fragmentPath = "", const std::string& albedo = "");
    void removeMaterialComponent(unsigned int entity);

    void addDirectionalLightComponent(unsigned int entity, const Vector3& direction = Vector3(), const Vector3& color = Vector3(1), const float intensity = 1);
    void removeDirectionalLightComponent(unsigned int entity);

    void addPointLightComponent(unsigned int entity, const Vector3& position = Vector3(), const Vector3& color = Vector3(1), const float intensity = 1, const float constant = 1, const float linear = 0.09f, const float quadratic = 0.032f);
    void removePointLightComponent(unsigned int entity);

    void addSpotLightComponent(unsigned int entity, const Vector3& position = Vector3(), const Vector3& direction = Vector3(), const Vector3& color = Vector3(1), const float intensity = 1, const float outerAngle = cos(45), const float innerAngle = cos(40), const float constant = 1, const float linear = 0.09f, const float quadratic = 0.032f);
    void removeSpotLightComponent(unsigned int entity);

    unsigned int addEntity();
    void removeEntity(unsigned int entity);

    void setSelectedEntity(unsigned int id);
    unsigned int getSelectedEntity();

  public:
    std::unordered_map<unsigned int, unsigned int> entities;
    std::unordered_map<unsigned int, Transform> transforms;
    std::unordered_map<unsigned int, MeshInstance> meshes;
    std::unordered_map<unsigned int, RigidBody> rigidBodys;
    std::unordered_map<unsigned int, Material> materials;
    std::unordered_map<unsigned int, DirectionalLight> directionalLights;
    std::unordered_map<unsigned int, PointLight> pointLights;
    std::unordered_map<unsigned int, SpotLight> spotLights;

  private:
    IDAllocator entityIDAllocator{1024};
    IDAllocator meshComponentIDAllocator{512};
    IDAllocator directionalLightComponentIDAllocator{512};
    IDAllocator pointLightComponentIDAllocator{512};
    IDAllocator spotLightComponentIDAllocator{512};

    void pickObject(const Ray ray);
    unsigned int selectedEntity = 0;

    std::string defaultAlbedo = ASSETS_PATH "textures/Albedo-Default.png";
    std::string defaultVertexShader = ASSETS_PATH "shaders/scene/vertexShader.vert";
    std::string defaultFragmentShader = ASSETS_PATH "shaders/scene/fragmentShader.frag";
    std::string defaultShadowVertexShader = ASSETS_PATH "shaders/scene/shadowShader.vert";
    std::string defaultShadowFragmentShader = ASSETS_PATH "shaders/scene/shadowShader.frag";
};