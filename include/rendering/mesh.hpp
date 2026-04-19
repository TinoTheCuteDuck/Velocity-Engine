#pragma once

#include <cstddef>
#include <mat4.hpp>
#include <string>
#include <vector2.hpp>
#include <vector3.hpp>

struct Vertex {
        Vector3 position;
        Vector2 UV;
        Vector3 normal;
};

class Mesh {
    public:
        unsigned int VAO, VBO, EBO;
        size_t indicesCount;
        Vector3 position;
        Vector3 scale;

        Mesh(const std::string& filePath);
        ~Mesh();
        Mat4 modelMatrice();

    private:
        void parseOBJ(const std::string& filePath);
};