#include "engineContext.hpp"
#include <GLFW/glfw3.h>
#include <cstring>
#include <input.hpp>
#include <vector2.hpp>

bool Input::currentKeys[GLFW_KEY_LAST + 1];
bool Input::previousKeys[GLFW_KEY_LAST + 1];
bool Input::currentMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
bool Input::previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];

Vector2 Input::mousePosition = Vector2();
Vector2 Input::previousMousePosition = Vector2();
Vector2 Input::scrollOffset = Vector2();

void Input::init(GLFWwindow* window) {
    std::memset(currentKeys, false, sizeof(currentKeys));
    std::memset(previousKeys, false, sizeof(previousKeys));
    std::memset(currentMouseButtons, false, sizeof(currentMouseButtons));
    std::memset(previousMouseButtons, false, sizeof(previousMouseButtons));

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS)
            currentKeys[key] = true;
        if (action == GLFW_RELEASE)
            currentKeys[key] = false;
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        if (action == GLFW_PRESS)
            currentMouseButtons[button] = true;
        if (action == GLFW_RELEASE)
            currentMouseButtons[button] = false;
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        mousePosition = Vector2(xpos, ypos);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        scrollOffset = Vector2(xoffset, yoffset);
    });
}

bool Input::isKeyHeld(int key) {
    if (key < 0 || key > GLFW_KEY_LAST)
        return false;
    return currentKeys[key];
}

bool Input::isKeyPressed(int key) {
    if (key < 0 || key > GLFW_KEY_LAST)
        return false;
    return currentKeys[key] && !previousKeys[key];
}

bool Input::isKeyReleased(int key) {
    if (key < 0 || key > GLFW_KEY_LAST)
        return false;
    return !currentKeys[key] && previousKeys[key];
}

bool Input::isButtonHeld(int button) {
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        return false;
    return currentMouseButtons[button];
}

bool Input::isButtonPressed(int button) {
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        return false;
    return currentMouseButtons[button] && !previousMouseButtons[button];
}

bool Input::isButtonReleased(int button) {
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        return false;
    return !currentMouseButtons[button] && previousMouseButtons[button];
}

Vector2 Input::getMouseDelta() {
    return mousePosition - previousMousePosition;
}

Vector2 Input::getMousePos() {
    return mousePosition;
}

Vector2 Input::getScrollOffset() {
    return scrollOffset;
}

void Input::setInputMode(int mode, int value) {
    glfwSetInputMode(gEngineContext.window->getWindow(), mode, value);
    previousMousePosition = mousePosition;
}

void Input::update() {
    std::memcpy(previousKeys, currentKeys, sizeof(currentKeys));
    std::memcpy(previousMouseButtons, currentMouseButtons, sizeof(currentMouseButtons));
    previousMousePosition = mousePosition;
    scrollOffset = Vector2();
}