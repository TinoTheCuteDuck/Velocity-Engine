#pragma once

#include "vector2.hpp"
#include <GLFW/glfw3.h>

class Input {
    private:
        static GLFWwindow* window;
        static double lastMouseX, lastMouseY;
        static Vector2 mouseDelta;
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    public:
        static void init(GLFWwindow* window);
        static void update();
        static bool isKeyPressed(int key);
        static Vector2 getMouseDelta();
        static void setMouseDelta(const Vector2& other);
};