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
        ~Engine();

        void run();

    private:
        void init();
        void update();
        void render();
        void shutdown();

    private:
        Window window;
        Shader sceneShader;
        Shader uiShader;
        Camera camera;
        Scene scene;
        Renderer renderer;

        double lastFPS = 0;
        double lastFrame = 0;
        int frames = 0;
        bool wasRightHeld = false;
};