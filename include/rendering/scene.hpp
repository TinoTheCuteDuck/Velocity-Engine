#pragma once

#include "core/idAllocator.hpp"
#include "physics/rigidBody.hpp"
#include "rendering/material.hpp"
#include "rendering/meshInstance.hpp"
#include "rendering/sceneECS.hpp"

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

  private:
    IDAllocator entityIDAllocator = IDAllocator(1024);

    void pickObject(const Ray ray);
    unsigned int selectedEntity = 0;

    std::string defaultAlbedo = ASSETS_PATH "textures/Albedo-Default.png";
    std::string defaultVertexShader = ASSETS_PATH "shaders/scene/vertexShader.vert";
    std::string defaultFragmentShader = ASSETS_PATH "shaders/scene/fragmentShader.frag";
};