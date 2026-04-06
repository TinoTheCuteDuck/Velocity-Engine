#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
    private:
        unsigned int vertexShader, fragmentShader, shaderProgram;
        std::string readFile(const std::string& filePath);
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
        void use();
};