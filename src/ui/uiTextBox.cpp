#include "GLFW/glfw3.h"
#include "ui/uiStructs.hpp"
#include <core/engine.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiText.hpp>
#include <ui/uiTextBox.hpp>
#include <ui/uiWidget.hpp>

UiTextBox::UiTextBox() {
    textObject = Engine::get().uiManager.addUiWidget<UiText>();
    textObject->position.set(Vector2(0.5f));
    textObject->anchorPoint.set(Vector2(0.5f));
    textObject->size.set(Vector2(1.0f));
    textObject->memory = sizeof(UiVertex) * 6 * 32;
    addChild(textObject);
}

void UiTextBox::update() {
    Input& input = Engine::get().input;
    hitDetection();

    // Get keyboard focus
    if (focused && input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        keyboardFocus = true;

    // Release keyboard focus
    if (!focused && input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        keyboardFocus = false;

    // Get characters
    if (keyboardFocus) {
        std::cout << "Current text: " << textObject->text.get() << std::endl;
        for (char character : input.getCurrentCharacter()) {
            if ((textObject->memory - (sizeof(UiVertex) * 6 * (textObject->text.get().size() + 1))) <= 0) {
                break;
            }
            textObject->text.set(textObject->text.get() + character);
            textObject->dirty = true;
        }
        if (input.isKeyPressed(GLFW_KEY_BACKSPACE)) {
            auto text = textObject->text.get();
            text.pop_back();
            textObject->text.set(text);
            textObject->dirty = true;
        }
    }

    // Default update
    UiWidget::update();
}