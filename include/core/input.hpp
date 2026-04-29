#pragma once

#include <GLFW/glfw3.h>
#include <vector2.hpp>

class Input {
    private:
        inline static GLFWwindow* glfwWindow;

        inline static bool currentKeys[GLFW_KEY_LAST + 1];
        inline static bool previousKeys[GLFW_KEY_LAST + 1];
        inline static bool currentMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
        inline static bool previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
        inline static Vector2 mousePosition;
        inline static Vector2 previousMousePosition;
        inline static Vector2 mouseDelta;
        inline static Vector2 scrollOffset;

    public:
        static void init(GLFWwindow* window);
        static void update();

        static bool isKeyHeld(int key);
        static bool isKeyPressed(int key);
        static bool isKeyReleased(int key);
        static bool isButtonHeld(int button);
        static bool isButtonPressed(int button);
        static bool isButtonReleased(int button);

        static Vector2 getMouseDelta();
        static Vector2 getMousePos();
        static Vector2 getScrollOffset();

        static void setInputMode(int mode, int value);
};