#pragma once

#include <string>

class Mat4;

class OpenGLShader {
  public:
    OpenGLShader(const char* vShaderSource, const char* fShaderSource);
    ~OpenGLShader();
    OpenGLShader(OpenGLShader&& other) noexcept;

  public:
    unsigned int vertexShader, fragmentShader, shaderProgram;
    int success;
    char infoLog[512];

  public:
    void use();
    void setBool(const std::string& name, const bool value) const;
    void setInt(const std::string& name, const int value) const;
    void setMat4(const std::string& name, const Mat4& mat) const;
};