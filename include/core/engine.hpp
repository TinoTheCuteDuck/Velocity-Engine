#pragma once

#include <core/engineTime.hpp>
#include <core/input.hpp>
#include <core/window.hpp>
#include <rendering/OpenGL/renderer.hpp>
#include <rendering/camera.hpp>
#include <rendering/scene.hpp>
#include <ui/uiManager.hpp>

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