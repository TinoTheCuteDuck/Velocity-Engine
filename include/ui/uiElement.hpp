#pragma once

#include <iostream>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class UiObject {
    private:
        std::array<float, 32> vertices;
        std::array<unsigned int, 6> indices;
        unsigned int VAO, VBO, EBO;
    public:
        UiObject(const float x, const float y, const float sizeX, const float sizeY, const std::string& texturePath);
        ~UiObject();
        void draw();
};