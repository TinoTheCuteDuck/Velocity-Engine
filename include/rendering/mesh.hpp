#pragma once

#include "math/vector2.hpp"
#include "math/vector3.hpp"
#include <string>

struct Vertex {
        Vector3 position;
        Vector2 UV;
        Vector3 normal;
};

class Mesh {
    public:
        Mesh(const std::string& filePath);
        ~Mesh();
        void draw();

    private:
        unsigned int VAO, VBO, EBO;
        int indicesCount;
        void parseOBJ(const std::string& filePath);
};