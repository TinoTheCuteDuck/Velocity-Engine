#include "rendering/meshData.hpp"

#include "core/engine.hpp"

#include <cfloat>
#include <fstream>
#include <sstream>

MeshData::MeshData(const std::string filePath) {
    this->filePath = filePath;

    parseOBJ(filePath);
    generateBoundingBox();
}

MeshData::~MeshData() {
    if (meshId)
        Engine::get().renderer.deleteGPUMesh(meshId);
}

MeshData::MeshData(MeshData&& other) noexcept {
    filePath = std::move(other.filePath);
    meshId = other.meshId;

    vertexData = std::move(other.vertexData);
    indices = std::move(other.indices);

    boundingBox = std::move(other.boundingBox);

    other.meshId = 0;
}

MeshData& MeshData::operator=(MeshData&& other) noexcept {
    if (this != &other) {
        Engine::get().renderer.deleteGPUMesh(meshId);

        filePath = std::move(other.filePath);
        meshId = other.meshId;

        vertexData = std::move(other.vertexData);
        indices = std::move(other.indices);

        boundingBox = std::move(other.boundingBox);

        other.meshId = 0;
    }
    return *this;
}

void MeshData::parseOBJ(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open mesh filepath: " + filePath);
    }
    std::string data;
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Vector2> UVs;

    int vertexCount = 0;

    while (std::getline(file, data)) {
        if (data.starts_with("v ")) {
            std::istringstream string(data.substr(2));
            float x, y, z;
            string >> x >> y >> z;
            vertices.push_back(Vector3(x, y, z));
        } else if (data.starts_with("vn")) {
            std::istringstream string(data.substr(2));
            float x, y, z;
            string >> x >> y >> z;
            normals.push_back(Vector3(x, y, z));
        } else if (data.starts_with("vt")) {
            std::istringstream string(data.substr(2));
            float x, y;
            string >> x >> y;
            UVs.push_back(Vector2(x, y));
        } else if (data.starts_with("f ")) {
            std::istringstream string(data.substr(2));
            std::string entry;
            while (string >> entry) {
                std::istringstream indicesF(entry);
                std::string token;
                std::vector<int> idx;
                while (std::getline(indicesF, token, '/')) {
                    idx.push_back(std::stoi(token) - 1);
                }
                vertexData.push_back(Vertex{vertices[idx[0]], UVs[idx[1]], normals[idx[2]]});
                indices.push_back(vertexCount);
                vertexCount += 1;
            }
        }
    }
    file.close();
}

void MeshData::generateBoundingBox() {
    Vector3 min(FLT_MAX);
    Vector3 max(-FLT_MAX);

    for (const auto& vertex : vertexData) {
        min.x = std::min(min.x, vertex.position.x);
        min.y = std::min(min.y, vertex.position.y);
        min.z = std::min(min.z, vertex.position.z);

        max.x = std::max(max.x, vertex.position.x);
        max.y = std::max(max.y, vertex.position.y);
        max.z = std::max(max.z, vertex.position.z);
    }

    if (vertexData.empty()) {
        boundingBox = BoundingBox{Vector3(), Vector3()};
        return;
    }

    boundingBox = BoundingBox{min, max};
}