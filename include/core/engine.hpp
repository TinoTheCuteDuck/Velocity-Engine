#pragma once

#include <camera.hpp>
#include <renderer.hpp>
#include <scene.hpp>
#include <uiManager.hpp>
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
        Renderer renderer;
        UiManager uiManager;
        Scene scene;
        Camera camera;
};