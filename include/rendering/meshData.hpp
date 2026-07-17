#pragma once

#include "rendering/renderingTypes.hpp"

#include <string>
#include <vector>

class MeshData {
  public:
    explicit MeshData(const std::string& filePath);
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
    void parseOBJ();
    void parseFace(std::vector<std::string>& parts, std::string& token);
    void parseGLTF();
    void generateBoundingBox();
};