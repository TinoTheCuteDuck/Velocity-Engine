#include <rendering/mesh.hpp>

#include <rendering/material.hpp>

#include <core/engine.hpp>
#include <core/ressources.hpp>

#include <math/matrices/mat4.hpp>
#include <math/vector/vector2.hpp>
#include <math/vector/vector3.hpp>

#include <algorithm>
#include <cfloat>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Mesh::Mesh(const std::string& filePath, Vector3 position, Vector3 scale) : position(position), scale(scale) {
    parseOBJ(filePath);
    meshID = Engine::get().renderer.addGPUMesh(vertexData, indices);
    material = Material{Ressources::pbrShader};
    generateBoundingBox();
}

Mesh::~Mesh() {
    Engine::get().renderer.deleteGPUMesh(meshID);
}

void Mesh::parseOBJ(const std::string& filePath) {
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
                vertexData.push_back(Vertex{vertices[idx[0]], UVs[idx[1]], normals[idx[2]], color});
                indices.push_back(vertexCount);
                vertexCount += 1;
            }
        }
    }
}

void Mesh::generateBoundingBox() {
    Vector3 min = Vector3(FLT_MAX);
    Vector3 max = Vector3(-FLT_MAX);
    for (Vertex& vertex : vertexData) {
        min.x = std::min(min.x, vertex.position.x);
        min.y = std::min(min.y, vertex.position.y);
        min.z = std::min(min.z, vertex.position.z);

        max.x = std::max(max.x, vertex.position.x);
        max.y = std::max(max.y, vertex.position.y);
        max.z = std::max(max.z, vertex.position.z);
    }
    boundingBox = BoundingBox{min, max};
}

Mat4 Mesh::modelMatrice() {
    return Mat4::translate(position) * Mat4::scale(scale);
}