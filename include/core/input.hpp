#pragma once

#include "GLFW/glfw3.h"
#include "math/vector/vector2.hpp"

#include <vector>

class Input {
  public:
    void init();
    void update();

    bool isKeyHeld(int key) const;
    bool isKeyPressed(int key) const;
    bool isKeyReleased(int key) const;
    bool isButtonHeld(int button) const;
    bool isButtonPressed(int button) const;
    bool isButtonReleased(int button) const;

    const std::vector<char>& getCurrentCharacter();

    Vector2 getMouseDelta() const;
    Vector2 getMousePos() const;
    Vector2 getScrollOffset() const;

    void setInputMode(int mode, int value);

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
};