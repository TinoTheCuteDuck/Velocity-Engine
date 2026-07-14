#include "rendering/OpenGL/OpenGLMesh.hpp"

#include "glad/glad.h"

OpenGLMesh::OpenGLMesh() : VAO(0), VBO(0), EBO(0), vertexCount(0) {
}

OpenGLMesh::OpenGLMesh(unsigned int VAO, unsigned int VBO, unsigned int EBO, size_t vertexCount) : VAO(VAO), VBO(VBO), EBO(EBO), vertexCount(vertexCount) {
}

OpenGLMesh::~OpenGLMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
}

OpenGLMesh::OpenGLMesh(OpenGLMesh&& other) noexcept {
    vertexCount = other.vertexCount;
    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;

    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
}