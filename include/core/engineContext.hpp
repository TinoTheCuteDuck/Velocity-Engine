#pragma once

#include <camera.hpp>
#include <renderer.hpp>
#include <shader.hpp>
#include <string>
#include <window.hpp>

struct EngineContext {
        std::string title = "Velocity Engine";
        int width = 1920, height = 1080;
        int FPS = 0;
        float FOV = 70;
        float flySpeed = 5.0f;
        float cursorSensitivity = 800.0f;
        float nearPlane = 0.1f;
        float farPlane = 5000.0f;
        double dt = 0;

        Window* window;
        Shader* sceneShader;
        Shader* uiShader;
        Camera* camera;
        Renderer* renderer;
};

extern EngineContext gEngineContext;