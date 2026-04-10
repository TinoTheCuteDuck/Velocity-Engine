#include "mat4.hpp"
#include <iostream>

#include <core/engineContext.hpp>
#include <rendering/camera.hpp>
#include <rendering/mesh.hpp>
#include <ui/uiManager.hpp>

//-----Settings-----
static const int width = 1920;
static const int height = 1080;
static const float FOV = 70;
static const float near = 0.1f;
static const float far = 5000.0f;

int main() {
    try {
        gEngineContext.width = width;
        gEngineContext.height = height;

        Window window(width, height, "Velocity Engine");
        Shader sceneShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag");
        Shader uiShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag");
        Camera camera(Vector3(0.0f, 2.0f, 5.0f));
        UiManager uiManager = UiManager();
        Mesh mesh(ASSETS_PATH "meshes/Vase.obj");

        gEngineContext.window = &window;
        gEngineContext.sceneShader = &sceneShader;
        gEngineContext.uiShader = &uiShader;

        while (!window.shouldClose()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            uiManager.draw();

            sceneShader.use();
            Mat4 projection = Mat4::projection(FOV, (float)gEngineContext.width / (float)gEngineContext.height, near, far);
            sceneShader.setMat4("projection", projection);

            Mat4 view = camera.getViewMatrix();
            sceneShader.setMat4("view", view);

            Mat4 model = Mat4::translate(Vector3());
            sceneShader.setMat4("model", model);

            mesh.draw();
            window.handleEvents();
        }
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}