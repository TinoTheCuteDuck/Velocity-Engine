#pragma once

#include <GLFW/glfw3.h>
#include <math/vector/vector2.hpp>

#include <vector>

class Input {
    private:
        bool currentKeys[GLFW_KEY_LAST + 1];
        bool previousKeys[GLFW_KEY_LAST + 1];
        bool currentMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
        bool previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];

        Vector2 mousePosition;
        Vector2 previousMousePosition;
        Vector2 mouseDelta;
        Vector2 scrollOffset;

        std::vector<char> currentCharacters;

    public:
        void init();
        void update();

        bool isKeyHeld(int key);
        bool isKeyPressed(int key);
        bool isKeyReleased(int key);
        bool isButtonHeld(int button);
        bool isButtonPressed(int button);
        bool isButtonReleased(int button);

        const std::vector<char>& getCurrentCharacter();

        Vector2 getMouseDelta();
        Vector2 getMousePos();
        Vector2 getScrollOffset();

        void setInputMode(int mode, int value);
};