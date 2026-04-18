#include "engineContext.hpp"
#include <renderer.hpp>

Renderer::Renderer() {
    commands.reserve(1024);
}

void Renderer::renderQueue(const RenderCall cmd) {
    commands.emplace_back(std::move(cmd));
}

void Renderer::startFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gEngineContext.sceneShader->use();

    Mat4 projection = Mat4::projection(gEngineContext.FOV, (float)gEngineContext.width / (float)gEngineContext.height, gEngineContext.nearPlane, gEngineContext.farPlane);
    gEngineContext.sceneShader->setMat4("projection", projection);
    gEngineContext.sceneShader->setMat4("view", gEngineContext.camera->getViewMatrix());
}

void Renderer::endFrame() {
    for (RenderCall& cmd : commands) {
        cmd.shader->use();
        cmd.shader->setMat4("model", cmd.transform);
        glBindVertexArray(cmd.vao);
        if (cmd.indexed) {
            glDrawElements(cmd.mode, cmd.count, cmd.indexType, 0);
        } else {
            glDrawArrays(cmd.mode, 0, cmd.count);
        }
    }
    commands.clear();
}