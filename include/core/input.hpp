#pragma once

#include <GLFW/glfw3.h>
#include <vector2.hpp>

class Input {
    private:
        static GLFWwindow* glfwWindow;

        static bool currentKeys[];
        static bool previousKeys[];
        static bool currentMouseButtons[];
        static bool previousMouseButtons[];
        static Vector2 mousePosition;
        static Vector2 previousMousePosition;
        static Vector2 mouseDelta;
        static Vector2 scrollOffset;

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