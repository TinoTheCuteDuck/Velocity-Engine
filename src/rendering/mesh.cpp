#include <mat4.hpp>
#include <material.hpp>
#include <mesh.hpp>
#include <renderer.hpp>
#include <ressources.hpp>
#include <vector2.hpp>
#include <vector3.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Mesh::Mesh(const std::string& filePath) : position(Vector3()), scale(Vector3(20)) {
    parseOBJ(filePath);
    meshID = Renderer::get().addGPUMesh(vertexData, indices);
    material = Material{Ressources::pbrShader};
}

Mesh::~Mesh() {
    Renderer::get().deleteGPUMesh(meshID);
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
                vertexData.push_back(Vertex{vertices[idx[0]], UVs[idx[1]], normals[idx[2]]});
                indices.push_back(vertexCount);
                vertexCount += 1;
            }
        }
    }
}

Mat4 Mesh::modelMatrice() {
    return Mat4::translate(position) * Mat4::scale(scale);
}