#pragma once

#include <rendering/material.hpp>

#include <math/matrices/mat4.hpp>
#include <math/vector/vector2.hpp>
#include <math/vector/vector3.hpp>

#include <string>
#include <vector>

struct Vertex {
        Vector3 position;
        Vector2 UV;
        Vector3 normal;
        Vector3 color;
};

struct BoundingBox {
        Vector3 min;
        Vector3 max;

        Vector3& operator[](int index) {
            return (index == 0) ? min : max;
        }
};

class Mesh {
    public:
        unsigned int meshID;
        Material material;
        Vector3 color = Vector3(1);

        std::vector<Vertex> vertexData;
        std::vector<unsigned int> indices;
        BoundingBox boundingBox;

        Mesh(const std::string& filePath);
        ~Mesh();

        Mesh(Mesh&& other) noexcept {
            meshID = other.meshID;
            material = std::move(other.material);
            color = other.color;
            vertexData = std::move(other.vertexData);
            indices = std::move(other.indices);
            boundingBox = std::move(other.boundingBox);

            other.meshID = 0;
        }

    private:
        void parseOBJ(const std::string& filePath);
        void generateBoundingBox();
};