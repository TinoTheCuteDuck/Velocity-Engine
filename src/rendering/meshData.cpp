#include "rendering/meshData.hpp"

#include "core/engine.hpp"

#include <cfloat>
#include <fstream>
#include <sstream>
#include <stdexcept>

MeshData::MeshData(const std::string& filePath) {
    this->filePath = filePath;

    parseOBJ();
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

    boundingBox = other.boundingBox;

    other.meshId = 0;
}

MeshData& MeshData::operator=(MeshData&& other) noexcept {
    if (this != &other) {
        Engine::get().renderer.deleteGPUMesh(meshId);

        filePath = std::move(other.filePath);
        meshId = other.meshId;

        vertexData = std::move(other.vertexData);
        indices = std::move(other.indices);

        boundingBox = other.boundingBox;

        other.meshId = 0;
    }

    return *this;
}

void MeshData::parseOBJ() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error reading mesh filepath: " + filePath);
    }

    std::string data;

    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Vector2> UVs;

    std::unordered_map<VertexKey, unsigned int> map;

    size_t vertexCount = 0;
    while (std::getline(file, data)) {
        float x, y, z;

        if (data.starts_with("v ")) {
            std::istringstream stream(data.substr(2));

            stream >> x >> y >> z;
            vertices.emplace_back(x, y, z);

        } else if (data.starts_with("vn ")) {
            std::istringstream stream(data.substr(3));

            stream >> x >> y >> z;
            normals.emplace_back(x, y, z);

        } else if (data.starts_with("vt ")) {
            std::istringstream stream(data.substr(3));

            stream >> x >> y;
            UVs.emplace_back(x, y);

        } else if (data.starts_with("f ")) {
            std::string string = data.substr(2);

            size_t tokenPos;
            while ((tokenPos = string.find(' ')) != std::string::npos) {
                std::string token = string.substr(0, tokenPos);
                std::vector<std::string> parts;

                parseFace(parts, token);

                Vector3 position = !parts[0].empty() ? vertices.at(std::stoi(parts[0]) - 1) : Vector3();
                Vector2 uv = !parts[1].empty() ? UVs.at(std::stoi(parts[1]) - 1) : Vector2();
                Vector3 normal = !parts[2].empty() ? normals.at(std::stoi(parts[2]) - 1) : Vector3();

                Vertex vertex{.position = position, .UV = uv, .normal = normal, .tangent = Vector3()};
                VertexKey key{
                    .v = !parts[0].empty() ? std::stoi(parts[0]) : -1,
                    .vt = !parts[1].empty() ? std::stoi(parts[1]) : -1,
                    .vn = !parts[2].empty() ? std::stoi(parts[2]) : -1,
                };

                auto it = map.find(key);
                if (it != map.end()) {
                    indices.push_back(it->second);
                } else {
                    indices.push_back(vertexCount);
                    map.emplace(key, vertexCount);
                    vertexData.push_back(vertex);
                    vertexCount++;
                }

                string = string.substr(tokenPos + 1);
            }

            if (!string.empty()) {
                std::vector<std::string> parts;
                parseFace(parts, string);

                Vector3 position = !parts[0].empty() ? vertices.at(std::stoi(parts[0]) - 1) : Vector3();
                Vector2 uv = !parts[1].empty() ? UVs.at(std::stoi(parts[1]) - 1) : Vector2();
                Vector3 normal = !parts[2].empty() ? normals.at(std::stoi(parts[2]) - 1) : Vector3();

                Vertex vertex{.position = position, .UV = uv, .normal = normal, .tangent = Vector3()};
                VertexKey key{
                    .v = !parts[0].empty() ? std::stoi(parts[0]) : -1,
                    .vt = !parts[1].empty() ? std::stoi(parts[1]) : -1,
                    .vn = !parts[2].empty() ? std::stoi(parts[2]) : -1,
                };

                if (auto it = map.find(key); it != map.end()) {
                    indices.push_back(it->second);
                } else {
                    indices.push_back(vertexCount);
                    map.emplace(key, vertexCount);
                    vertexData.push_back(vertex);
                    vertexCount++;
                }
            }
        }
    }

    for (size_t i = 0; i < indices.size(); i += 3) {
        Vertex& v1 = vertexData.at(indices[i]);
        Vertex& v2 = vertexData.at(indices[i + 1]);
        Vertex& v3 = vertexData.at(indices[i + 2]);

        Vector3 edge1 = v2.position - v1.position;
        Vector3 edge2 = v3.position - v1.position;
        Vector2 deltaUV1 = v2.UV - v1.UV;
        Vector2 deltaUV2 = v3.UV - v1.UV;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        Vector3 tangent;
        tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

        v1.tangent += tangent;
        v2.tangent += tangent;
        v3.tangent += tangent;
    };

    for (Vertex& vertex : vertexData) {
        vertex.tangent = vertex.tangent.normalize();
    }

    file.close();
}

void MeshData::parseFace(std::vector<std::string>& parts, std::string& token) {
    size_t slashPos;
    while ((slashPos = token.find('/')) != std::string::npos) {
        parts.push_back(token.substr(0, slashPos));
        token = token.substr(slashPos + 1);
    }

    if (!token.empty()) {
        parts.push_back(token);
    }

    for (size_t i = parts.size(); i < 3; i++) {
        parts.emplace_back("");
    }
}

void MeshData::parseGLTF() {
    struct Accessor {
        std::string type;
        int componentType;
        int count;
        int bufferView;
        int byteOffset;
    };

    std::fstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error opening glTF file at: " + filePath;
    }

    std::string data;

    while (std::getline(file, data)) {
        if (data.find("asset")) {
        }
    }
};

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
        boundingBox = BoundingBox{.min = Vector3(), .max = Vector3()};
        return;
    }

    boundingBox = BoundingBox{.min = min, .max = max};
}