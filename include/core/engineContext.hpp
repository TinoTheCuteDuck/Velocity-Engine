#pragma once

#include <core/window.hpp>
#include <rendering/shader.hpp>

struct EngineContext {
        int width, height;
        double dt;
        float flySpeed;
        float cursorSensitivity;
        float FOV;
        Window* window;
        Shader* sceneShader;
        Shader* uiShader;
};

extern EngineContext gEngineContext;