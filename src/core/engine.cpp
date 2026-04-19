#include <GLFW/glfw3.h>
#include <engine.hpp>
#include <engineContext.hpp>
#include <engineUi.hpp>
#include <glad/glad.h>
#include <input.hpp>
#include <mat4.hpp>
#include <shader.hpp>
#include <uiManager.hpp>

Engine::Engine()
    : window(gEngineContext.width, gEngineContext.height, gEngineContext.title),
      sceneShader(ASSETS_PATH "shaders/scene/vertexShader.vert", ASSETS_PATH "shaders/scene/fragmentShader.frag"),
      uiShader(ASSETS_PATH "shaders/ui/uiVertexShader.vert", ASSETS_PATH "shaders/ui/uiFragmentShader.frag"),
      camera(Vector3(0, 2, 3)),
      scene(Scene()),
      renderer(Renderer()) {

    init();
}

Engine::~Engine() {
}

void Engine::init() {
    gEngineContext.window = &window;
    gEngineContext.sceneShader = &sceneShader;
    gEngineContext.uiShader = &uiShader;
    gEngineContext.camera = &camera;
    gEngineContext.renderer = &renderer;

    Input::init(window.getWindow());
    UiManager::init();
    setupUi();

    lastFPS = glfwGetTime();
    lastFrame = glfwGetTime();
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
    double now = glfwGetTime();
    gEngineContext.dt = now - lastFrame;
    lastFrame = now;

    frames++;
    if ((now - lastFPS) > 1) {
        gEngineContext.FPS = frames;
        lastFPS = now;
        frames = 0;
    }

    camera.update();
    Input::update();
}

void Engine::render() {
    renderer.startFrame();

    scene.submit();
    UiManager::submit();

    renderer.endFrame();
}

void Engine::shutdown() {
    UiManager::shutdown();
}