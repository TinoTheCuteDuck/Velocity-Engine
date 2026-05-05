#pragma once

#include <camera.hpp>
#include <engineTime.hpp>
#include <input.hpp>
#include <renderer.hpp>
#include <scene.hpp>
#include <uiManager.hpp>
#include <window.hpp>

class Engine {
    public:
        static Engine& get();
        static void setInstance(Engine& engine);

        Engine();
        void run();

    public:
        Window window;
        Renderer renderer;
        Input input;
        EngineTime time;
        UiManager uiManager;
        Scene scene;
        Camera camera;

    private:
        void init();
        void update();
        void render();

    private:
        inline static Engine* instance = nullptr;
};