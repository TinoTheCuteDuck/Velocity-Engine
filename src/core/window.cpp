#include <window.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdexcept>

Window::Window(const int width, const int height, const std::string& title, bool vsync) {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW failed to initialize!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("The window failed to initialize!");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        Window* win = (Window*)glfwGetWindowUserPointer(window);
        if (win->onResize)
            win->onResize(width, height);
    });

    if (!vsync) {
        glfwSwapInterval(0);
    }
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