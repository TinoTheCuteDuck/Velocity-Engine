#pragma once

#include <string>

class ShaderData {
  public:
    ShaderData(const std::string vertexShaderPath, const std::string fragmentShaderPath);
    ~ShaderData();

    ShaderData(const ShaderData&) = delete;
    ShaderData& operator=(const ShaderData&) = delete;

    ShaderData(ShaderData&& other) noexcept;
    ShaderData& operator=(ShaderData&& other) noexcept;

  public:
    unsigned int shaderId = 0;

    std::string vertexShaderPath;
    std::string fragmentShaderPath;

    std::string vShaderSource;
    std::string fShaderSource;

  private:
    std::string parseShader(std::string& filePath);
};