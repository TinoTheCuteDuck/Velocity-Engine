#include <core/input.hpp>

#include <GLFW/glfw3.h>
#include <core/engine.hpp>

#include <cstring>

void Input::init() {
    GLFWwindow* window = Engine::get().window.getWindow();

    std::memset(currentKeys, false, sizeof(currentKeys));
    std::memset(previousKeys, false, sizeof(previousKeys));
    std::memset(currentMouseButtons, false, sizeof(currentMouseButtons));
    std::memset(previousMouseButtons, false, sizeof(previousMouseButtons));

    glfwSetKeyCallback(window, []([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
        Input& input = Engine::get().input;
        if (action == GLFW_PRESS)
            input.currentKeys[key] = true;
        if (action == GLFW_RELEASE)
            input.currentKeys[key] = false;
    });

    glfwSetMouseButtonCallback(window, []([[maybe_unused]] GLFWwindow* window, int button, int action, [[maybe_unused]] int mods) {
        Input& input = Engine::get().input;
        if (action == GLFW_PRESS)
            input.currentMouseButtons[button] = true;
        if (action == GLFW_RELEASE)
            input.currentMouseButtons[button] = false;
    });

    glfwSetCursorPosCallback(window, []([[maybe_unused]] GLFWwindow* window, double xpos, double ypos) {
        Input& input = Engine::get().input;
        input.mousePosition = Vector2(xpos, ypos);
    });

    glfwSetScrollCallback(window, []([[maybe_unused]] GLFWwindow* window, double xoffset, double yoffset) {
        Input& input = Engine::get().input;
        input.scrollOffset = Vector2(xoffset, yoffset);
    });
}

bool Input::isKeyHeld(int key) {
    if (key < 0 || key > GLFW_KEY_LAST)
        return false;
    return currentKeys[key] && previousKeys[key];
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
    return currentMouseButtons[button] && previousMouseButtons[button];
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
    GLFWwindow* window = Engine::get().window.getWindow();

    glfwSetInputMode(window, mode, value);
    previousMousePosition = mousePosition;
}

void Input::update() {
    std::memcpy(previousKeys, currentKeys, sizeof(currentKeys));
    std::memcpy(previousMouseButtons, currentMouseButtons, sizeof(currentMouseButtons));
    previousMousePosition = mousePosition;
    scrollOffset = Vector2();
}