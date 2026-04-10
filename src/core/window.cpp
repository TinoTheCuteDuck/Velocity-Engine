#include "shader.hpp"
#include <core/engineContext.hpp>
#include <core/window.hpp>

Window::Window(const int width, const int height, const std::string& title) {
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Glad has failed to initialize!");
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

Window::~Window() {
    glfwTerminate();
}

void Window::handleEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() {
    return window;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    gEngineContext.width = width;
    gEngineContext.height = height;
    glViewport(0, 0, width, height);
}