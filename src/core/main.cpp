#include "GLFW/glfw3.h"
#include "input.hpp"
#include "mat4.hpp"
#include "vector3.hpp"
#include <iostream>

#include <core/engineContext.hpp>
#include <rendering/camera.hpp>
#include <rendering/mesh.hpp>
#include <ui/uiManager.hpp>

//-----Settings-----
static const int width = 1920;
static const int height = 1080;
static const float FOV = 70;
static const float flySpeed = 5.0f;
static const float cursorSensitivity = 0.1f;
static const float near = 0.1f;
static const float far = 5000.0f;

int main() {
    try {
        gEngineContext.width = width;
        gEngineContext.height = height;
        gEngineContext.FOV = FOV;
        gEngineContext.flySpeed = flySpeed;
        gEngineContext.cursorSensitivity = cursorSensitivity;

        Window window(width, height, "Velocity Engine");
        Shader sceneShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag");
        Shader uiShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag");
        Camera camera(Vector3(0.0f, 2.0f, 5.0f));
        Mesh mesh(ASSETS_PATH "meshes/stanford-bunny.obj");

        gEngineContext.window = &window;
        gEngineContext.sceneShader = &sceneShader;
        gEngineContext.uiShader = &uiShader;

        Input::init(window.getWindow());
        UiManager::init();

        double lastFPS = glfwGetTime();
        double lastFrame = glfwGetTime();
        int frames = 0;

        while (!window.shouldClose()) {
            double now = glfwGetTime();
            gEngineContext.dt = now - lastFrame;
            lastFrame = now;
            frames += 1;
            if ((now - lastFPS) > 1) {
                std::cout << "FPS: " << frames << std::endl;
                lastFPS = now;
                frames = 0;
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            camera.update();

            sceneShader.use();
            Mat4 projection = Mat4::projection(FOV, (float)gEngineContext.width / (float)gEngineContext.height, near, far);
            sceneShader.setMat4("projection", projection);

            Mat4 view = camera.getViewMatrix();
            sceneShader.setMat4("view", view);

            Mat4 model = Mat4::translate(Vector3()) * Mat4::scale(Vector3(20));
            sceneShader.setMat4("model", model);
            mesh.draw();

            glDisable(GL_DEPTH_TEST);
            UiManager::draw();
            glEnable(GL_DEPTH_TEST);

            window.handleEvents();
        }
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}