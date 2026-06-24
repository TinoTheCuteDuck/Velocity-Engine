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

struct VertexKey {
    int v;
    int vt;
    int vn;

    bool operator==(const VertexKey& other) const {
        return v == other.v &&
               vt == other.vt &&
               vn == other.vn;
    }
};

namespace std {
template <>
struct hash<VertexKey> {
    size_t operator()(const VertexKey& k) const {
        return (k.v * 73856093) ^ (k.vt * 19349663) ^ (k.vn * 83492791);
    }
};
}  // namespace std

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
    void parseFace(std::vector<std::string>& parts, std::string& token);
    void generateBoundingBox();
};