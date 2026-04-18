#pragma once

#include <cstddef>
#include <glad/glad.h>
#include <mat4.hpp>
#include <shader.hpp>
#include <vector>

struct RenderCall {
        Shader* shader;
        GLuint vao;
        GLenum mode;
        GLenum indexType;
        size_t count;
        bool indexed;
        Mat4 transform;
};

class Renderer {
    public:
        Renderer();
        void renderQueue(const RenderCall cmd);
        void startFrame();
        void endFrame();

    private:
        std::vector<RenderCall> commands;
};