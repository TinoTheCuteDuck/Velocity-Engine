#include <core/engine.hpp>

#include <core/engineTime.hpp>
#include <core/input.hpp>
#include <core/ressources.hpp>

#include <rendering/OpenGL/renderer.hpp>
#include <rendering/camera.hpp>

#include <ui/engineUi.hpp>
#include <ui/uiManager.hpp>

Engine::Engine() : window(), renderer(), input(), time(), uiManager(), scene(), camera() {
    init();
}

void Engine::init() {
    Engine::setInstance(*this);

    Ressources::pbrShader = renderer.addShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag");
    Ressources::uiShader = renderer.addShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag");
    Ressources::uiTexture = renderer.addTexture(ASSETS_PATH "textures/DejaVu Sans Mono.png", GL_REPEAT, GL_NEAREST, false);

    input.init();
    uiManager.load();
    scene.load();
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