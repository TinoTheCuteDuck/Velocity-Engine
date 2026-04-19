#pragma once

#include <camera.hpp>
#include <mesh.hpp>
#include <renderer.hpp>
#include <scene.hpp>
#include <shader.hpp>
#include <window.hpp>

class Engine {
    public:
        Engine();
        void run();

    private:
        void init();
        void update();
        void render();
        void shutdown();
        void updateTime();

    private:
        Window window;
        Shader sceneShader;
        Shader uiShader;
        Camera camera;
        Scene scene;
        Renderer renderer;
};