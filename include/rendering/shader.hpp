#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <mat4.hpp>

class Shader {
    private:
        unsigned int vertexShader, fragmentShader, shaderProgram;
        std::string readFile(const std::string& filePath);

    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        Shader(Shader&& other) noexcept : vertexShader(other.vertexShader), fragmentShader(other.fragmentShader), shaderProgram(other.shaderProgram) {
            other.shaderProgram = 0;
        }

        Shader& operator=(Shader&& other) noexcept {
            if (this != &other) {
                if (shaderProgram)
                    glDeleteProgram(shaderProgram);
                vertexShader = other.vertexShader;
                fragmentShader = other.fragmentShader;
                shaderProgram = other.shaderProgram;
                other.shaderProgram = 0;
            }
            return *this;
        }

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        void use();
        void setMat4(const std::string& name, const Mat4& mat) const;
        void setInt(const std::string& name, const int value) const;
        void setBool(const std::string& name, const bool value) const;
};