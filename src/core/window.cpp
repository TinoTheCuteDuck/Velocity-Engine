#include "core/window.hpp"

#include "GLFW/glfw3.h"
#include "core/engine.hpp"
#include "glad/glad.h"
#include "math/vector/vector2.hpp"

#include <stdexcept>

Window::Window() {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW failed to initialize!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowSize.x, windowSize.y, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("The window failed to initialize!");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        glViewport(0, 0, width, height);
        win->setWindowSize(width, height);
    });

    glfwSwapInterval(vsync ? 1 : 0);
}

Window::~Window() {
    glfwTerminate();
}

void Window::pollEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() {
    return window;
}

bool Window::getVsync() {
    return vsync;
}

std::string& Window::getTitle() {
    return title;
}

Vector2 Window::getWindowSize() {
    return windowSize;
}

void Window::setVsync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::setWindowSize(int width, int height) {
    windowSize = Vector2(width, height);
    Engine::get().uiManager.reRender();
}