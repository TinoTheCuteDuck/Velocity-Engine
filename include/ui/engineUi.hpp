#pragma once

#include <GLFW/glfw3.h>
#include <core/engine.hpp>
#include <math/vector/vector2.hpp>
#include <memory>
#include <ui/uiButton.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiSlider.hpp>
#include <ui/uiText.hpp>
#include <ui/uiTextBox.hpp>
#include <ui/uiWidget.hpp>

inline void loadUi() {
    UiManager& manager = Engine::get().uiManager;

    {
        auto test = manager.addUiWidget<UiWidget>();
        test->position.set(Vector2(0.016f, 0.54f));
        test->size.set(Vector2(0.13f, 0.87f));
        test->cornerRadius.set(0.03f);
        test->anchorPoint.set(Vector2(0.0f, 0.5f));
        test->opacity.set(0.5f);
        test->updateCallback = [test]() {
            Vector2 mousePos = Engine::get().input.getMousePos();
            Vector2 windowSize = Engine::get().window.getWindowSize();

            Vector2 in(0.016f, 0.54f);
            Vector2 out(-0.3f, 0.54f);
            Vector2 position = test->position.get();
            if ((mousePos.x / windowSize.x) <= 0.2f) {
                if (position != in)
                    test->playAnimation(in, 0.2f);
            } else {
                if (position != out)
                    test->playAnimation(out, 0.2f);
            }
        };

        {
            auto test3 = manager.addUiWidget<UiText>();
            test3->position.set(Vector2(0.5f, 0.01));
            test3->anchorPoint.set(Vector2(0.5f, 0));
            test3->memory = sizeof(UiVertex) * 6 * 24;
            test3->text.set("FPS: 0");
            test3->textSize.set(32.0f / 1080.0f);
            test3->textCallback = [test3]() {
                test3->text.set("FPS: " + std::to_string(Engine::get().time.getFPS()));
            };
            test->addChild(test3);
        }
    }

    {
        auto button = manager.addUiWidget<UiButton>();
        button->position.set(Vector2(0.5, 0.3));
        button->anchorPoint.set(Vector2(0.5, 0.5));
        button->size.set(Vector2(0.1, 0.1));
        button->color.set(Vector3(1.0f, 0, 0));
        button->onMouseButton1Click = [button]() {
            Renderer& renderer = Engine::get().renderer;
            renderer.enableWireframe(!renderer.getWireframeEnabled());
            button->color.set(renderer.getWireframeEnabled() ? Vector3(1.0f, 0, 0) : Vector3(0, 0, 1.0f));
        };
    }
    {
        auto dragAble = manager.addUiWidget<UiSlider>();
        dragAble->position.set(Vector2(0.5, 0.7));
        dragAble->size.set(Vector2(0.1));
        dragAble->aspect.set(1.0f);
        dragAble->color.set(Vector3(0.1, 1, 0.1));
        dragAble->onDragStart = [dragAble]() {
            Vector2 mousePos = Engine::get().input.getMousePos();
            Vector2 windowSize = Engine::get().window.getWindowSize();

            Vector2 offset = mousePos - dragAble->getAbsolutePosition();
            Vector2 normalizedOffset = Vector2(offset.x / windowSize.x, offset.y / windowSize.y);
            dragAble->dragOffset.set(normalizedOffset);
        };
        dragAble->onDrag = [dragAble]() {
            Vector2 mousePos = Engine::get().input.getMousePos();
            Vector2 windowSize = Engine::get().window.getWindowSize();
            Vector2 normalizedPos = Vector2(mousePos.x / windowSize.x, mousePos.y / windowSize.y);
            dragAble->position.set(normalizedPos - dragAble->dragOffset.get());
            dragAble->dirty = true;
        };
    }
    {
        auto textBox = manager.addUiWidget<UiTextBox>();
        textBox->position.set(Vector2(0.5f));
        textBox->size.set(Vector2(0.1f));
        textBox->aspect.set(1.0f);
        textBox->color.set(Vector3(0.0f, 1.0f, 1.0f));
        textBox->opacity.set(0.0f);
    }
}