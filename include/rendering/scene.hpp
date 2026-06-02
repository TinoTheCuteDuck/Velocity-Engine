#pragma once

#include <core/idAllocator.hpp>
#include <core/input.hpp>
#include <math/ray.hpp>
#include <physics/rigidBody.hpp>
#include <rendering/camera.hpp>
#include <rendering/mesh.hpp>
#include <rendering/sceneECS.hpp>
#include <unordered_map>

class Scene {
  public:
    void load();
    void update();
    void submit();

    void addTransformComponent(unsigned int entity, Transform&& transform);
    void removeTransformComponent(const unsigned int entity);

    void addMeshComponent(unsigned int entity, Mesh&& mesh);
    void removeMeshComponent(unsigned int entity);

    void addRigidBodyComponent(unsigned int entity, RigidBody&& body);
    void removeRigidBodyComponent(unsigned int entity);

    unsigned int addEntity();
    void removeEntity(unsigned int entity);

    unsigned int getSelectedEntity();

  public:
    // Components
    std::unordered_map<unsigned int, unsigned int> entities;
    std::unordered_map<unsigned int, Transform> transforms;
    std::unordered_map<unsigned int, Mesh> meshes;
    std::unordered_map<unsigned int, RigidBody> rigidBodys;

  private:
    IDAllocator entityIDAllocator = IDAllocator(1024);

    void pickObject(const Ray ray);
    unsigned int selectedEntity = 0;
};