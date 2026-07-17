#include "ui/widgets/uiButton.hpp"

#include "GLFW/glfw3.h"
#include "core/engine.hpp"
#include "core/input.hpp"

// Update override
void UiButton::update() {
    const Input& input = Engine::get().input;
    hitDetection();

    // Click Detection
    if (focused && enabled) {
        if (input.isButtonReleased(GLFW_MOUSE_BUTTON_LEFT)) {
            if (onMouseButton1Up) {
                onMouseButton1Up();
                dirty = true;
            }
        }
        if (input.isButtonHeld(GLFW_MOUSE_BUTTON_LEFT)) {
            if (onMouseButton1Down) {
                onMouseButton1Down();
                dirty = true;
            }
        }
        if (input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            if (onMouseButton1Click) {
                onMouseButton1Click();
                dirty = true;
            }
        }
        if (input.isButtonReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
            if (onMouseButton2Up) {
                onMouseButton2Up();
                dirty = true;
            }
        }
        if (input.isButtonHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
            if (onMouseButton2Down) {
                onMouseButton2Down();
                dirty = true;
            }
        }
        if (input.isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            if (onMouseButton2Click) {
                onMouseButton2Click();
                dirty = true;
            }
        }
    }

    UiWidget::update();
}