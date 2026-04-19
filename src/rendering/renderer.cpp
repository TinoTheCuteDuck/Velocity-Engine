#include <engineState.hpp>
#include <renderer.hpp>

Renderer::Renderer() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    commands.reserve(1024);
}

void Renderer::renderQueue(const RenderCall cmd) {
    commands.emplace_back(std::move(cmd));
}

void Renderer::startFrame(Shader& sceneShader, Camera& camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sceneShader.use();

    Mat4 projection = Mat4::projection(EngineState::settings.FOV, (float)EngineState::viewport.width / (float)EngineState::viewport.height, EngineState::settings.nearPlane, EngineState::settings.farPlane);
    sceneShader.setMat4("projection", projection);
    sceneShader.setMat4("view", camera.getViewMatrix());
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