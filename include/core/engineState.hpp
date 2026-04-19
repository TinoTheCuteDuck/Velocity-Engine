#pragma once

#include <string>

struct WindowConfig {
        std::string title = "Velocity Engine";
};

struct Viewport {
        int width = 1920;
        int height = 1080;
};

struct FrameState {
        int FPS = 0;
        double dt = 0;
};

struct EngineConfig {
        float FOV = 70.0f;
        float flySpeed = 5.0f;
        float cursorSensitivity = 800.0f;
        float nearPlane = 0.1f;
        float farPlane = 5000.0f;
};

namespace EngineState {
inline Viewport viewport;
inline FrameState frame;
inline EngineConfig settings;
inline WindowConfig windowSettings;
} // namespace EngineState