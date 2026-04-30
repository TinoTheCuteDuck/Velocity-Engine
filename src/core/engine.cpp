#include <engine.hpp>

#include <engineState.hpp>
#include <engineUi.hpp>
#include <ressources.hpp>
#include <uiManager.hpp>
#include <vector3.hpp>

#include <input.hpp>
#include <renderer.hpp>
#include <time.hpp>

Engine::Engine()
    : window(EngineState::viewport.width, EngineState::viewport.height, EngineState::windowSettings.title, false),
      renderer(),
      uiManager(),
      scene(),
      camera(Vector3(20, 15, 30)) {

    init();
}

void Engine::init() {
    window.onResize = [](int width, int height) {
        EngineState::viewport.width = width;
        EngineState::viewport.height = height;
    };

    Renderer::setInstance(renderer);
    UiManager::setInstance(uiManager);
    Input::init(window.getWindow());

    Ressources::pbrShader = renderer.addShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag");
    Ressources::uiShader = renderer.addShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag");
    Ressources::uiTexture = renderer.addTexture(ASSETS_PATH "textures/DejaVu Sans Mono.png", GL_REPEAT, GL_NEAREST, false);

    setupUi();
    uiManager.load();
    scene.load();
}

void Engine::run() {
    while (!window.shouldClose()) {
        update();
        render();
        window.pollEvents();
    }
    shutdown();
}

void Engine::update() {
    updateTime();
    camera.update();

    Input::update();
    uiManager.update();
    scene.update();
}

void Engine::render() {
    renderer.startFrame(camera);

    scene.submit();
    uiManager.submit();

    renderer.endFrame();
}

void Engine::shutdown() {
}

void Engine::updateTime() {
    Time::update();
    EngineState::frame.dt = Time::getDt();
    EngineState::frame.FPS = Time::getFPS();
}