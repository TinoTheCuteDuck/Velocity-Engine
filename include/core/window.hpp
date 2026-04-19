#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <glad/glad.h>
#include <string>

class Window {
    private:
        GLFWwindow* window;

    public:
        Window(const int width, const int height, const std::string& title, bool vsync = false);
        ~Window();

        bool shouldClose();
        void handleEvents();
        GLFWwindow* getWindow();
        std::function<void(int, int)> onResize;
};