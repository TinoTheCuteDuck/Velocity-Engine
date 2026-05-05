#include <uiButton.hpp>

#include <engine.hpp>
#include <input.hpp>
#include <vector2.hpp>

UiButton::UiButton() {
}

bool UiButton::isHovered() {
    Vector2 mousePos = Engine::get().input.getMousePos();
    if (mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
        mousePos.y >= position.y && mousePos.y <= position.y + size.y) {
        return true;
    }
    return false;
}

bool UiButton::isPressed() {
    if (isHovered() && Engine::get().input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        return true;
    }
    return false;
}