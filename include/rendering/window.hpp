#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow* window;
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    public:
        Window(const int width, const int height, const std::string& title);
        ~Window();
        void handleEvents();
        bool shouldClose();
        GLFWwindow* getWindow();
};