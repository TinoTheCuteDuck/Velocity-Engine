#include "rendering/OpenGL/OpenGLShader.hpp"

#include "glad/glad.h"
#include "math/matrices/mat4.hpp"

#include <cstddef>
#include <stdexcept>

OpenGLShader::OpenGLShader(const char* vShaderSource, const char* fShaderSource) {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Vertex shader compilation failed: \n") + infoLog);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Fragment shader compilation failed: \n") + infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Shader program linking failed: \n") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

OpenGLShader::~OpenGLShader() {
    glDeleteProgram(shaderProgram);
}

OpenGLShader::OpenGLShader(OpenGLShader&& other) noexcept {
    shaderProgram = other.shaderProgram;
    other.shaderProgram = 0;
}

void OpenGLShader::use() {
    glUseProgram(shaderProgram);
}

void OpenGLShader::setBool(const std::string& name, const bool value) const {
    int loc = glGetUniformLocation(shaderProgram, name.c_str());
    if (loc == -1) {
        // std::cout << "Uniform bool not found: " + name << std::endl;
        return;
    }
    glUniform1i(loc, value);
}

void OpenGLShader::setInt(const std::string& name, const int value) const {
    int loc = glGetUniformLocation(shaderProgram, name.c_str());
    if (loc == -1) {
        // std::cout << "Uniform int not found: " + name << std::endl;
        return;
    }
    glUniform1i(loc, value);
}

void OpenGLShader::setMat4(const std::string& name, const Mat4& mat) const {
    int loc = glGetUniformLocation(shaderProgram, name.c_str());
    if (loc == -1) {
        // std::cout << "Uniform mat4 not found: " + name << std::endl;
        return;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, &mat.m[0]);
}
