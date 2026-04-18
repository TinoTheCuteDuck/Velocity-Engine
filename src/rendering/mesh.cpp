#include <mat4.hpp>
#include <mesh.hpp>
#include <shader.hpp>
#include <vector2.hpp>
#include <vector3.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Mesh::Mesh(const std::string& filePath) : position(Vector3()), scale(Vector3(20)) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    parseOBJ(filePath);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
    std::vector<Vertex> vertexData;
    std::vector<unsigned int> indices;
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
    indicesCount = indices.size();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

Mat4 Mesh::modelMatrice() {
    return Mat4::translate(position) * Mat4::scale(scale);
}

void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}