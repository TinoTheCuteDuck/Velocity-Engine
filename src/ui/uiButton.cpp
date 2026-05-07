#include <uiButton.hpp>

#include <engine.hpp>
#include <input.hpp>
#include <vector2.hpp>

UiButton::UiButton() {
}

void UiButton::update() {
    if (updateCallback) {
        updateCallback();
    }

    Input& input = Engine::get().input;
    Vector2 mousePos = input.getMousePos();

    isHovered = false;
    isPressed = false;
    isHeld = false;

    bool inside = mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
                  mousePos.y >= position.y && mousePos.y <= position.y + size.y;

    if (inside) {
        isHovered = true;
        if (input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            isPressed = true;
            if (onClick)
                onClick();
        }

        isHeld = input.isButtonHeld(GLFW_MOUSE_BUTTON_LEFT);
        if (isHeld && onHold) {
            onHold();
        }
    }

    if (!wasHovered && isHovered) {
        if (onHover)
            onHover();
    }

    if (wasHovered && !isHovered) {
        if (onHoverEnd)
            onHoverEnd();
    }

    if (wasHeld && !isHeld) {
        if (onHoldEnd)
            onHoldEnd();
    }

    wasHovered = isHovered;
    wasHeld = isHeld;
}

void UiButton::setOnClick(const std::function<void()>& callback) {
    onClick = callback;
}

void UiButton::setOnHover(const std::function<void()>& callback) {
    onHover = callback;
}

void UiButton::setOnHoverEnd(const std::function<void()>& callback) {
    onHoverEnd = callback;
}

void UiButton::setOnHold(const std::function<void()>& callback) {
    onHold = callback;
}

void UiButton::setOnHoldEnd(const std::function<void()>& callback) {
    onHoldEnd = callback;
}
