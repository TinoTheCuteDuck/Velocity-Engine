#include <engine.hpp>
#include <engineState.hpp>
#include <engineUi.hpp>
#include <input.hpp>
#include <ressources.hpp>
#include <time.hpp>
#include <uiManager.hpp>

Engine::Engine()
    : window(EngineState::viewport.width, EngineState::viewport.height, EngineState::windowSettings.title),
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
    setupUi();

    Ressources::pbrShader = renderer.addShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag");
    Ressources::uiShader = renderer.addShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag");
    Ressources::uiTexture = renderer.addTexture(ASSETS_PATH "textures/DejaVu Sans Mono.png", GL_REPEAT, GL_NEAREST, false);

    Renderer::setInstance(renderer);
    Input::init(window.getWindow());
    UiManager::init();

    scene.load();
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
    UiManager::update();
    camera.update();
    Input::update();
}

void Engine::render() {
    renderer.startFrame(camera);

    scene.submit();
    UiManager::submit();

    renderer.endFrame();
}

void Engine::shutdown() {
}

void Engine::updateTime() {
    Time::update();
    EngineState::frame.dt = Time::getDt();
    EngineState::frame.FPS = Time::getFPS();
}