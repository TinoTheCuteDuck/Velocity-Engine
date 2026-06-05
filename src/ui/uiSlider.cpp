#include <core/engine.hpp>
#include <ui/uiSlider.hpp>
#include <ui/uiWidget.hpp>

void UiSlider::update() {
    Input& input = Engine::get().input;
    hitDetection();

    // Detect dragging and fire events
    dragging = false;
    if (enabled) {
        if (focused && input.isButtonHeld(GLFW_MOUSE_BUTTON_LEFT))
            dragging = true;

        if (!wasDragging && dragging) {
            if (onDragStart)
                onDragStart();
        }

        if (wasDragging && !dragging) {
            if (onDragEnd)
                onDragEnd();
        }

        if (wasDragging && dragging) {
            if (onDrag)
                onDrag();
        }

        wasDragging = dragging;
    }

    UiWidget::update();
}