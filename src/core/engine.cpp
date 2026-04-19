#include <GLFW/glfw3.h>
#include <engine.hpp>
#include <engineState.hpp>
#include <engineUi.hpp>
#include <glad/glad.h>
#include <input.hpp>
#include <mat4.hpp>
#include <shader.hpp>
#include <time.hpp>
#include <uiManager.hpp>

Engine::Engine()
    : window(EngineState::viewport.width, EngineState::viewport.height, EngineState::windowSettings.title),
      sceneShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag"),
      uiShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag"),
      camera(Vector3(0, 2, 3)),
      scene(Scene()),
      renderer(Renderer()) {

    init();
}

void Engine::init() {
    window.onResize = [](int width, int height) {
        EngineState::viewport.width = width;
        EngineState::viewport.height = height;
    };
    Input::init(window.getWindow());
    UiManager::init();
    setupUi();
}

void Engine::run() {
    while (!window.shouldClose()) {
        update();
        render();
        window.handleEvents();
    }
    shutdown();
}

void Engine::update() {
    updateTime();
    camera.update();
    Input::update();
}

void Engine::render() {
    renderer.startFrame(sceneShader, camera);

    scene.submit(renderer, sceneShader);
    UiManager::submit(renderer, uiShader);

    renderer.endFrame();
}

void Engine::shutdown() {
    UiManager::shutdown();
}

void Engine::updateTime() {
    Time::update();
    EngineState::frame.dt = Time::getDt();
    EngineState::frame.FPS = Time::getFPS();
}