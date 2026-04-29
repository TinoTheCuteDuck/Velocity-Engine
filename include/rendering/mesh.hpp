#pragma once

#include <mat4.hpp>
#include <material.hpp>
#include <string>
#include <vector2.hpp>
#include <vector3.hpp>
#include <vector>

struct Vertex {
        Vector3 position;
        Vector2 UV;
        Vector3 normal;
};

class Mesh {
    public:
        unsigned int meshID;
        Material material;

        Vector3 position;
        Vector3 scale;

        std::vector<Vertex> vertexData;
        std::vector<unsigned int> indices;

        Mesh(const std::string& filePath);
        ~Mesh();

        Mat4 modelMatrice();

    private:
        void parseOBJ(const std::string& filePath);
};