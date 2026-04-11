#include "GLFW/glfw3.h"
#include "vector2.hpp"
#include <input.hpp>

GLFWwindow* Input::window = nullptr;
double Input::lastMouseX = 0.0;
double Input::lastMouseY = 0.0;
Vector2 Input::mouseDelta = Vector2();

void Input::init(GLFWwindow* glWindow) {
    window = glWindow;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Input::mouse_callback);
}

void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    double offsetX = xpos - lastMouseX;
    double offsetY = ypos - lastMouseY;
    lastMouseX = xpos;
    lastMouseY = ypos;

    mouseDelta = Vector2(offsetX, offsetY);
}

bool Input::isKeyPressed(int key) {
    if (glfwGetKey(window, key) == GLFW_PRESS)
        return true;
    return false;
}

Vector2 Input::getMouseDelta() {
    return mouseDelta;
}

void Input::setMouseDelta(const Vector2& other) {
    mouseDelta = other;
}