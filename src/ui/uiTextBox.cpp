#include <GLFW/glfw3.h>
#include <core/engine.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiStructs.hpp>
#include <ui/uiText.hpp>
#include <ui/uiTextBox.hpp>
#include <ui/uiWidget.hpp>

UiTextBox::UiTextBox() {
    auto text = std::make_unique<UiText>();
    text->position.set(Vector2(0.5f));
    text->anchorPoint.set(Vector2(0.5f));
    text->size.set(Vector2(1.0f));
    text->memory = sizeof(UiVertex) * 6 * 64;
    textObject = text.get();
    addChild(std::move(text));
}

void UiTextBox::update() {
    Input& input = Engine::get().input;
    hitDetection();

    if (enabled) {
        // Get keyboard focus
        if (focused && input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && !keyboardFocus) {
            keyboardFocus = true;
            Engine::get().camera.movementBlocked = true;

            if (onKeyboardFocusCallback)
                onKeyboardFocusCallback();
        }

        // Release keyboard focus
        if (!focused && input.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && keyboardFocus) {
            keyboardFocus = false;
            Engine::get().camera.movementBlocked = false;

            if (onKeyboardFocusLostCallback)
                onKeyboardFocusLostCallback();
        }

        // Get characters
        if (keyboardFocus) {
            for (char character : input.getCurrentCharacter()) {
                if ((textObject->memory - (sizeof(UiVertex) * 6 * (textObject->text.get().size() + 1))) <= 0) {
                    break;
                }
                textObject->text.set(textObject->text.get() + character);
                textObject->dirty = true;
            }
            if (input.isKeyPressed(GLFW_KEY_BACKSPACE)) {
                auto text = textObject->text.get();
                if (text.size() >= 1) {
                    text.pop_back();
                    textObject->text.set(text);
                    textObject->dirty = true;
                }
            }
            if (input.isKeyPressed(GLFW_KEY_ENTER)) {
                keyboardFocus = false;
                Engine::get().camera.movementBlocked = false;

                if (onKeyboardFocusLostCallback)
                    onKeyboardFocusLostCallback();
            }
        }
    }

    // Default update
    UiWidget::update();
}