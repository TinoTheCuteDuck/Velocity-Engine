#include <fstream>
#include <shader.hpp>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vShaderSource = vertexCode.c_str();
    const char* fShaderSource = fragmentCode.c_str();

    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Vertex shader compilation failed!: ") + infoLog);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Fragment shader compilation failed!: ") + infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Shader linking failed!: ") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

std::string Shader::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Couldn't read shader filepath!");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::setBool(const std::string& name, const bool value) const {
    int loc = glGetUniformLocation(shaderProgram, name.c_str());
    if (loc == -1) {
        std::cout << "Uniform not found: " + name << std::endl;
        // throw std::runtime_error("Uniform not found: " + name);
    }
    glUniform1i(loc, value);
}

void Shader::setInt(const std::string& name, const int value) const {
    int loc = glGetUniformLocation(shaderProgram, name.c_str());
    if (loc == -1) {
        std::cout << "Uniform not found: " + name << std::endl;
        throw std::runtime_error("Uniform not found: " + name);
    }
    glUniform1i(loc, value);
}

void Shader::setMat4(const std::string& name, const Mat4& mat) const {
    int loc = glGetUniformLocation(shaderProgram, name.c_str());
    if (loc == -1) {
        std::cout << "Uniform not found: " + name << std::endl;
        throw std::runtime_error("Uniform not found: " + name);
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, &mat.m[0]);
}