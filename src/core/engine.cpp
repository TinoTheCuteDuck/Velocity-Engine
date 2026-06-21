#include "core/engine.hpp"

Engine::Engine() : window(), renderer(), assetManager(), input(), time(), uiManager(), scene(), camera() {
    init();
}

void Engine::init() {
    Engine::setInstance(*this);

    input.init();
    scene.load();
    uiManager.load();
}

void Engine::run() {
    while (!window.shouldClose()) {
        window.pollEvents();
        update();
        render();
    }
}

void Engine::update() {
    time.update();
    camera.update();
    assetManager.update();

    uiManager.update();
    scene.update();
    input.update();
}

void Engine::render() {
    renderer.startFrame();

    scene.submit();
    uiManager.submit();

    renderer.endFrame();
}

Engine& Engine::get() {
    return *instance;
}

void Engine::setInstance(Engine& engine) {
    instance = &engine;
}