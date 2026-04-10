#pragma once

#include <core/window.hpp>
#include <rendering/shader.hpp>

struct EngineContext {
        int width, height;
        Window* window;
        Shader* sceneShader;
        Shader* uiShader;
};

extern EngineContext gEngineContext;