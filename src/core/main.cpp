#include <iostream>
#include <vector>
#include <memory>
#include <rendering/window.hpp>
#include <rendering/shader.hpp>
#include <ui/uiObject.hpp>

//-----Settings-----
static const int width = 1920;
static const int height = 1080;

int main() {
    try {
        Window window(width, height, "Hello World");
        Shader sceneShader(ASSETS_PATH"shaders/scene/vertexShader.vert", ASSETS_PATH"shaders/scene/fragmentShader.frag");
        Shader uiShader(ASSETS_PATH"shaders/ui/uiVertexShader.vert", ASSETS_PATH"shaders/ui/uiFragmentShader.frag");

        std::vector<std::unique_ptr<UiObject>> uiElements;
        uiElements.push_back(std::make_unique<UiObject>(0, 1, 0.2, 1, "Hello"));

        while (!window.shouldClose()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            uiShader.use();
            for (auto& uiElement : uiElements) {
                uiElement->draw();
            }

            sceneShader.use();
            window.handleEvents();
        }
    } catch(std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}