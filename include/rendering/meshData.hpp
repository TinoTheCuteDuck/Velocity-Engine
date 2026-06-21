#pragma once

#include "math/vector/vector2.hpp"
#include "math/vector/vector3.hpp"

#include <string>
#include <vector>

struct Vertex {
    Vector3 position;
    Vector2 UV;
    Vector3 normal;
};

struct BoundingBox {
    Vector3 min;
    Vector3 max;

    Vector3& operator[](int index) {
        return (index == 0) ? min : max;
    }
};

class MeshData {
  public:
    MeshData(const std::string filePath);
    ~MeshData();

    MeshData(const MeshData&) = delete;
    MeshData& operator=(const MeshData&) = delete;

    MeshData(MeshData&& other) noexcept;
    MeshData& operator=(MeshData&& other) noexcept;

  public:
    std::string filePath;
    unsigned int meshId = 0;

    std::vector<Vertex> vertexData;
    std::vector<unsigned int> indices;

    BoundingBox boundingBox;

  private:
    void parseOBJ(const std::string& filePath);
    void generateBoundingBox();
};