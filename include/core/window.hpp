#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class Window {
    private:
        GLFWwindow* window;

    public:
        Window(const int width, const int height, const std::string& title, bool vsync = false);
        ~Window();

        void pollEvents();
        bool shouldClose();

        GLFWwindow* getWindow();
        std::function<void(int, int)> onResize;
};