#pragma once

#include "rendering/renderingTypes.hpp"

#include <string>

class MeshInstance {
  public:
    MeshInstance(const std::string& filePath, const unsigned int componentID);
    MeshInstance(MeshInstance&& other) noexcept;

  public:
    unsigned int componentID;
    std::string filePath;

    MeshAttribute<Vector3> color{Vector3(1)};
    MeshAttribute<float> opacity{1};

  private:
    void generateMeshInstanceData();
};