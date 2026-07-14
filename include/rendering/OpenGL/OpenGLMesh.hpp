#pragma once

#include <cstddef>

class OpenGLMesh {
  public:
    OpenGLMesh();
    OpenGLMesh(unsigned int VAO, unsigned int VBO, unsigned int EBO, size_t vertexCount);

    ~OpenGLMesh();
    OpenGLMesh(OpenGLMesh&& other) noexcept;

  public:
    unsigned int VAO, VBO, EBO;
    size_t vertexCount;
};