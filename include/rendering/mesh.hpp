#pragma once

#include <material.hpp>

#include <mat4.hpp>
#include <vector2.hpp>
#include <vector3.hpp>

#include <string>
#include <vector>

struct Vertex {
        Vector3 position;
        Vector2 UV;
        Vector3 normal;
};

struct BoundingBox {
        Vector3 min;
        Vector3 max;
};

class Mesh {
    public:
        unsigned int meshID;
        Material material;

        Vector3 position;
        Vector3 scale;

        std::vector<Vertex> vertexData;
        std::vector<unsigned int> indices;
        BoundingBox boundingBox;

        Mesh(const std::string& filePath, Vector3 position, float scale);
        ~Mesh();

        Mat4 modelMatrice();

    private:
        void parseOBJ(const std::string& filePath);
        void generateBoundingBox();
};