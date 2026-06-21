#include "rendering/OpenGL/OpenGLMesh.hpp"

#include "glad/glad.h"

OpenGLMesh::OpenGLMesh() : VAO(0), VBO(0), EBO(0), UBO(0), vertexCount(0) {
}

OpenGLMesh::OpenGLMesh(unsigned int VAO, unsigned int VBO, unsigned int EBO, unsigned int UBO, size_t vertexCount) : VAO(VAO), VBO(VBO), EBO(EBO), UBO(UBO), vertexCount(vertexCount) {
}

OpenGLMesh::~OpenGLMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
    if (UBO != 0) {
        glDeleteBuffers(1, &UBO);
    }
}

OpenGLMesh::OpenGLMesh(OpenGLMesh&& other) noexcept {
    vertexCount = other.vertexCount;
    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;
    UBO = other.UBO;

    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
    other.UBO = 0;
}