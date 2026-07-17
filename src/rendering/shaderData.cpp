#include "rendering/shaderData.hpp"

#include "core/engine.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

ShaderData::ShaderData(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) : vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath) {
    vShaderSource = parseShader(vertexShaderPath);
    fShaderSource = parseShader(fragmentShaderPath);
}

ShaderData::~ShaderData() {
    if (shaderId)
        Engine::get().renderer.deleteShader(shaderId);
}

ShaderData::ShaderData(ShaderData&& other) noexcept {
    shaderId = other.shaderId;

    vertexShaderPath = std::move(other.vertexShaderPath);
    fragmentShaderPath = std::move(other.fragmentShaderPath);

    vShaderSource = std::move(other.vShaderSource);
    fShaderSource = std::move(other.fShaderSource);

    other.shaderId = 0;
}

ShaderData& ShaderData::operator=(ShaderData&& other) noexcept {
    if (this != &other) {
        Engine::get().renderer.deleteShader(shaderId);

        shaderId = other.shaderId;

        vertexShaderPath = std::move(other.vertexShaderPath);
        fragmentShaderPath = std::move(other.fragmentShaderPath);

        vShaderSource = std::move(other.vShaderSource);
        fShaderSource = std::move(other.fShaderSource);

        other.shaderId = 0;
    }
    return *this;
}

std::string ShaderData::parseShader(const std::string& filePath) {
    std::fstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Error parsing shader");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}