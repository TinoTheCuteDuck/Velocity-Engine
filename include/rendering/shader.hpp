#pragma once

#include "math/mat4.hpp"
#include <GLFW/glfw3.h>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

class Shader {
    private:
        unsigned int vertexShader, fragmentShader, shaderProgram;
        std::string readFile(const std::string& filePath);

    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
        void use();
        void setMat4(const std::string& name, const Mat4& mat) const;
        void setInt(const std::string& name, const int num) const;
};