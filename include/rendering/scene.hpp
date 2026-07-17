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

    void addTransformComponent(unsigned int entity, const Vector3& position = Vector3(), const Vector3& scale = Vector3(1), const Vector3& rotation = Vector3(0));
    void removeTransformComponent(unsigned int entity);

    void addMeshComponent(unsigned int entity, const std::string& filePath);
    void removeMeshComponent(unsigned int entity);

    void addRigidBodyComponent(unsigned int entity, const RigidBody&& body);
    void removeRigidBodyComponent(unsigned int entity);

    void addMaterialComponent(unsigned int entity, const std::string& vertexPath = "", const std::string& fragmentPath = "", const std::string& albedo = "", const std::string& normal = "", const std::string& metallic = "", const std::string& roughness = "", const std::string& ao = "");
    void removeMaterialComponent(unsigned int entity);

    void addDirectionalLightComponent(unsigned int entity, const Vector3& direction = Vector3(), const Vector3& color = Vector3(1), float intensity = 1);
    void removeDirectionalLightComponent(unsigned int entity);

    void addPointLightComponent(unsigned int entity, const Vector3& position = Vector3(), const Vector3& color = Vector3(1), float intensity = 1, float constant = 1, float linear = 0.09f, float quadratic = 0.032f);
    void removePointLightComponent(unsigned int entity);

    void addSpotLightComponent(unsigned int entity, const Vector3& position = Vector3(), const Vector3& direction = Vector3(), const Vector3& color = Vector3(1), float intensity = 1, float outerAngle = cos(45), float innerAngle = cos(40), float constant = 1, float linear = 0.09f, float quadratic = 0.032f);
    void removeSpotLightComponent(unsigned int entity);

    unsigned int addEntity();
    void removeEntity(unsigned int entity);

    void setSelectedEntity(unsigned int id);
    unsigned int getSelectedEntity() const;

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

    void pickObject(const Ray& ray);
    unsigned int selectedEntity = 0;

    std::string defaultAlbedo = ASSETS_PATH "textures/Albedo-Default.png";
    std::string defaultNormal = ASSETS_PATH "textures/Normal-Default.png";
    std::string defaultMetallic = ASSETS_PATH "textures/Metallic-Default.png";
    std::string defaultRoughness = ASSETS_PATH "textures/Roughness-Default.png";
    std::string defaultAO = ASSETS_PATH "textures/AO-Default.png";

    std::string defaultVertexShader = ASSETS_PATH "shaders/scene/vertexShader.vert";
    std::string defaultFragmentShader = ASSETS_PATH "shaders/scene/fragmentShader.frag";
    std::string defaultShadowVertexShader = ASSETS_PATH "shaders/scene/shadowShader.vert";
    std::string defaultShadowFragmentShader = ASSETS_PATH "shaders/scene/shadowShader.frag";
};