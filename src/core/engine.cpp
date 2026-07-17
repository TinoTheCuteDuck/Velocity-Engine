#include "core/engine.hpp"

Engine::Engine() : input() {
    init();
}

void Engine::init() {
    setInstance(*this);

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

    //std::cout << "FPS: " << time.getFPS() << std::endl;

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