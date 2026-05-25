#pragma once

#include <GLFW/glfw3.h>
#include <core/engine.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiText.hpp>
#include <ui/uiWidget.hpp>

inline void loadUi() {
    UiManager& manager = Engine::get().uiManager;

    {
        UiWidget* test = manager.addUiWidget(std::make_unique<UiWidget>());
        test->setPosition(Vector2(0.016f, 0.54f));
        test->setSize(Vector2(0.13f, 0.87f), false);
        test->setCornerRadius(0.03f);
        test->setAnchorPoint(Vector2(0.0f, 0.5f));
        test->setOpacity(0.5f);
        test->setUpdateCallback([test]() {
            Vector2 mousePos = Engine::get().input.getMousePos();
            Vector2 windowSize = Engine::get().window.getWindowSize();

            Vector2 in(0.016f, 0.54f);
            Vector2 out(-0.3f, 0.54f);
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
    {
        UiText* test2 = static_cast<UiText*>(manager.addUiWidget(std::make_unique<UiText>()));
        test2->setPosition(Vector2(0.5, 0.5));
        test2->setAnchorPoint(Vector2(0.5, 0.5));
        test2->setText("Hello World!", 48.0f / 1080.0f);
        test2->setMemory(sizeof(UiVertex) * 6 * 12);
    }
    {
        UiText* test3 = static_cast<UiText*>(manager.addUiWidget(std::make_unique<UiText>()));
        test3->setPosition(Vector2(0.5, 0.4));
        test3->setAnchorPoint(Vector2(0.5, 0.5));
        test3->setMemory(sizeof(UiVertex) * 6 * 24);
        test3->setText("FPS: 0", 48.0f / 1080.0f);
        test3->setTextCallback([test3]() {
            test3->setText("FPS: " + std::to_string(Engine::get().time.getFPS()), 48.0f / 1080.0f);
        });
    }
}