#pragma once

#include <GLFW/glfw3.h>
#include <vector2.hpp>

#include <string>

class Window {
    public:
        Window();
        ~Window();

        void pollEvents();
        bool shouldClose();

        bool getVsync();
        Vector2 getWindowSize();
        GLFWwindow* getWindow();
        std::string& getTitle();

        void setVsync(bool enabled);
        void setWindowSize(int width, int height);

    private:
        bool vsync = false;
        std::string title = "Velocity Engine";
        Vector2 windowSize = Vector2(1920, 1080);

        GLFWwindow* window;
};