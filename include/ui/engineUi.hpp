#pragma once

#include <GLFW/glfw3.h>
#include <core/engine.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiWidget.hpp>

inline void loadUi() {
    UiManager& manager = Engine::get().uiManager;
    UiWidget* test = manager.addUiWidget(std::make_unique<UiWidget>());
    test->setPosition(Vector2(-0.3f, 0.102f));
    test->setSize(Vector2(0.13f, 0.87f));
    test->setCornerRadius(30.0f);
    test->setUpdateCallback([test]() {
        Vector2 mousePos = Engine::get().input.getMousePos();
        Vector2 windowSize = Engine::get().window.getWindowSize();

        Vector2 in(0.016f, 0.102f);
        Vector2 out(-0.3f, 0.102f);
        Vector2 position = test->getPosition();
        if ((mousePos.x / windowSize.x) <= 0.2f) {
            if (position != in)
                test->playAnimation(in, 0.2f);
        } else {
            if (position != out)
                test->playAnimation(out, 0.2f);
        }
    });
}