#pragma once

#include <GLFW/glfw3.h>
#include <core/engine.hpp>
#include <math/vector/vector2.hpp>
#include <ui/uiButton.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiSlider.hpp>
#include <ui/uiStructs.hpp>
#include <ui/uiText.hpp>
#include <ui/uiTextBox.hpp>
#include <ui/uiWidget.hpp>

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

inline std::string setPrecision(float number, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << number;
    return ss.str();
};

inline std::string setPrecision(Vector3& vector, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << vector.x << ", " << vector.y << ", " << vector.z;
    return ss.str();
}

inline void loadUi() {
    UiManager& manager = Engine::get().uiManager;
    Vector3 bg_dark(26.0f / 255.0f, 27.0f / 255.0f, 38.0f / 255.0f);
    Vector3 bg_main(45.0f / 255.0f, 47.0f / 255.0f, 65.0f / 255.0f);
    Vector3 text(192.0f / 255.0f, 202.0f / 255.0f, 245.0f / 255.0f);
    Vector3 accent_active(122.0f / 255.0f, 162.0f / 255.0f, 247.0f / 255.0f);
    Vector3 accent_inactive(65.0f / 255.0f, 72.0f / 255.0f, 104.0f / 255.0f);
    // Vector3 tertiary(40.0f / 255.0f, 52.0f / 255.0f, 87.0f / 255.0f);

    {
        auto inspector = manager.addUiWidget<UiWidget>();
        inspector->position.set(Vector2(-0.3f, 580.0f / 1080.0f));
        inspector->anchorPoint.set(Vector2(0.5f));
        inspector->size.set(Vector2(250.0f / 1920.0f, 940.0f / 1080.0f));
        inspector->cornerRadius.set(60.0f / 1080.0f);
        inspector->color.set(bg_main);
        inspector->borderColor.set(Vector4(accent_inactive, 1.0f));
        inspector->borderSize.set(4.0f / 1080.0f);
        inspector->mouseEnterCallback = [inspector, accent_active] {
            inspector->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                inspector->borderColor.get(),
                Vector4(accent_active, 1.0f),
                0.2f,
                WidgetAnimationBase::COLOR,
                [inspector](const Vector4& updatedColor) {
                    inspector->borderColor.set(updatedColor);
                    inspector->dirty = true;
                }));
        };
        inspector->mouseLeaveCallback = [inspector, accent_inactive] {
            inspector->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                inspector->borderColor.get(),
                Vector4(accent_inactive, 1.0f),
                0.2f,
                WidgetAnimationBase::COLOR,
                [inspector](const Vector4& updatedColor) {
                    inspector->borderColor.set(updatedColor);
                    inspector->dirty = true;
                }));
        };
        inspector->updateCallback = [inspector] {
            static Vector2 inspectorTarget = Vector2(-0.3f, 580.0f / 1080.0f);

            Vector2 newTarget = Engine::get().scene.getSelectedObject()
                                    ? Vector2(155.0f / 1920.0f, 580.0f / 1080.0f)
                                    : Vector2(-0.3f, 580.0f / 1080.0f);

            if (newTarget != inspectorTarget) {
                inspectorTarget = newTarget;

                inspector->playAnimation(std::make_unique<WidgetAnimation<Vector2>>(
                    inspector->position.get(),
                    newTarget,
                    0.3f,
                    WidgetAnimationBase::POSITION,
                    [inspector](const Vector2& updatedPosition) {
                        inspector->position.set(updatedPosition);
                        inspector->dirty = true;
                    }));
            }
        };

        {
            auto header = std::make_shared<UiWidget>();
            header->position.set(Vector2(0.0f));
            header->size.set(Vector2(1.0f, 70.0f / 1080.0f));
            header->color.set(bg_dark);

            inspector->addChild(header);

            {
                auto headerText = std::make_shared<UiText>();
                headerText->position.set(Vector2(0.5f));
                headerText->anchorPoint.set(Vector2(0.5f));
                headerText->text.set("Properties");
                headerText->color.set(text);
                headerText->textSize.set(32.0f / 1080.0f);
                headerText->memory = sizeof(UiVertex) * 6 * headerText->text.get().size();

                header->addChild(headerText);
            }

            {
                auto positionLabel = std::make_shared<UiWidget>();
                positionLabel->position.set(Vector2(0.5f, 0.112f));
                positionLabel->size.set(Vector2(0.96f, 0.045f));
                positionLabel->anchorPoint.set(Vector2(0.5f));
                positionLabel->color.set(bg_dark);
                positionLabel->borderSize.set(3.0f / 1080.0f);
                positionLabel->borderColor.set(Vector4(accent_inactive, 1.0f));
                positionLabel->cornerRadius.set(20.0f / 1080.0f);
                positionLabel->mouseEnterCallback = [positionLabel, accent_active] {
                    positionLabel->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                        positionLabel->borderColor.get(),
                        Vector4(accent_active, 1.0f),
                        0.2f,
                        WidgetAnimationBase::COLOR,
                        [positionLabel](const Vector4& updatedColor) {
                            positionLabel->borderColor.set(updatedColor);
                            positionLabel->dirty = true;
                        }));
                };
                positionLabel->mouseLeaveCallback = [positionLabel, accent_inactive] {
                    positionLabel->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                        positionLabel->borderColor.get(),
                        Vector4(accent_inactive, 1.0f),
                        0.2f,
                        WidgetAnimationBase::COLOR,
                        [positionLabel](const Vector4& updatedColor) {
                            positionLabel->borderColor.set(updatedColor);
                            positionLabel->dirty = true;
                        }));
                };

                inspector->addChild(positionLabel);

                {
                    auto positionText = std::make_shared<UiText>();
                    positionText->position.set(Vector2(0.0f, 0.5f));
                    positionText->anchorPoint.set(Vector2(0.0f, 0.5f));
                    positionText->color.set(text);
                    positionText->text.set(" Position:");
                    positionText->textSize.set(16.0f / 1080.0f);
                    positionText->memory = sizeof(UiVertex) * 6 * positionText->text.get().size();

                    positionLabel->addChild(positionText);

                    auto positionValue = std::make_shared<UiTextBox>();
                    positionValue->position.set(Vector2(0.4f, 0.5f));
                    positionValue->size.set(Vector2(0.58f, 1.0f));
                    positionValue->anchorPoint.set(Vector2(0.0f, 0.5f));
                    positionValue->opacity.set(0.0f);
                    positionValue->color.set(text);
                    positionValue->textObject->text.set("");
                    positionValue->textObject->textSize.set(15.0f / 1080.0f);
                    positionValue->textObject->color.set(text);
                    positionValue->memory = sizeof(UiVertex) * 6 * 24;
                    positionValue->updateCallback = [positionValue] {
                        if (Engine::get().scene.getSelectedObject() && !positionValue->keyboardFocus) {
                            Vector3 position = Engine::get().scene.getSelectedObject()->mesh->position;
                            positionValue->textObject->text.set(setPrecision(position, 2));
                            positionValue->dirty = true;
                        }
                    };
                    positionValue->onKeyboardFocusCallback = [positionValue] {
                        positionValue->textObject->text.set("");
                        positionValue->dirty = true;
                    };
                    positionValue->onKeyboardFocusLostCallback = [positionValue] {
                        positionValue->dirty = true;

                        std::string input = positionValue->textObject->text.get();
                        std::istringstream ss(input);
                        float x, y, z;
                        char comma;

                        if (!Engine::get().scene.getSelectedObject()) {
                            positionValue->textObject->text.set("");
                            return;
                        }

                        auto obj = Engine::get().scene.getSelectedObject();

                        if (ss >> x >> comma >> y >> comma >> z) {
                            obj->mesh->position = Vector3(x, y, z);
                            if (obj->body) {
                                obj->body->position = Vector3(x, y, z);
                            }
                        } else {
                            positionValue->textObject->text.set(setPrecision(obj->mesh->position, 2));
                        }
                    };
                    positionLabel->addChild(positionValue);
                }
            }

            {
                auto colorLabel = std::make_shared<UiWidget>();
                colorLabel->position.set(Vector2(0.5f, 0.165f));
                colorLabel->size.set(Vector2(0.96f, 0.045f));
                colorLabel->anchorPoint.set(Vector2(0.5f));
                colorLabel->color.set(bg_dark);
                colorLabel->borderSize.set(3.0f / 1080.0f);
                colorLabel->borderColor.set(Vector4(accent_inactive, 1.0f));
                colorLabel->cornerRadius.set(20.0f / 1080.0f);
                colorLabel->mouseEnterCallback = [colorLabel, accent_active] {
                    colorLabel->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                        colorLabel->borderColor.get(),
                        Vector4(accent_active, 1.0f),
                        0.2f,
                        WidgetAnimationBase::COLOR,
                        [colorLabel](const Vector4& updatedColor) {
                            colorLabel->borderColor.set(updatedColor);
                            colorLabel->dirty = true;
                        }));
                };
                colorLabel->mouseLeaveCallback = [colorLabel, accent_inactive] {
                    colorLabel->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                        colorLabel->borderColor.get(),
                        Vector4(accent_inactive, 1.0f),
                        0.2f,
                        WidgetAnimationBase::COLOR,
                        [colorLabel](const Vector4& updatedColor) {
                            colorLabel->borderColor.set(updatedColor);
                            colorLabel->dirty = true;
                        }));
                };

                inspector->addChild(colorLabel);
                {
                    auto colorText = std::make_shared<UiText>();
                    colorText->position.set(Vector2(0.0f, 0.5f));
                    colorText->anchorPoint.set(Vector2(0.0f, 0.5f));
                    colorText->color.set(text);
                    colorText->text.set(" Color:");
                    colorText->textSize.set(16.0f / 1080.0f);
                    colorText->memory = sizeof(UiVertex) * 6 * colorText->text.get().size();

                    colorLabel->addChild(colorText);

                    auto colorValue = std::make_shared<UiTextBox>();
                    colorValue->position.set(Vector2(0.35f, 0.5f));
                    colorValue->size.set(Vector2(0.63f, 1.0f));
                    colorValue->anchorPoint.set(Vector2(0.0f, 0.5f));
                    colorValue->opacity.set(0.0f);
                    colorValue->color.set(text);
                    colorValue->textObject->text.set("");
                    colorValue->textObject->textSize.set(15.0f / 1080.0f);
                    colorValue->textObject->color.set(text);
                    colorValue->memory = sizeof(UiVertex) * 6 * 24;
                    colorValue->updateCallback = [colorValue] {
                        if (Engine::get().scene.getSelectedObject() && !colorValue->keyboardFocus) {
                            Vector3 color = Engine::get().scene.getSelectedObject()->mesh->color * 255;
                            colorValue->textObject->text.set(setPrecision(color, 0));
                            colorValue->dirty = true;
                        }
                    };
                    colorValue->onKeyboardFocusCallback = [colorValue] {
                        colorValue->textObject->text.set("");
                        colorValue->dirty = true;
                    };
                    colorValue->onKeyboardFocusLostCallback = [colorValue] {
                        colorValue->dirty = true;

                        std::string input = colorValue->textObject->text.get();
                        std::istringstream ss(input);
                        float x, y, z;
                        char comma;

                        if (!Engine::get().scene.getSelectedObject()) {
                            colorValue->textObject->text.set("");
                            return;
                        }

                        auto obj = Engine::get().scene.getSelectedObject();

                        if (ss >> x >> comma >> y >> comma >> z) {
                            obj->mesh->color = Vector3(x, y, z) / 255;
                        } else {
                            Vector3 color = obj->mesh->color * 255;
                            colorValue->textObject->text.set(setPrecision(color, 0));
                        }
                    };
                    colorLabel->addChild(colorValue);
                }
            }

            {
                auto scaleLabel = std::make_shared<UiWidget>();
                scaleLabel->position.set(Vector2(0.5f, 0.21825f));
                scaleLabel->size.set(Vector2(0.96f, 0.045f));
                scaleLabel->anchorPoint.set(Vector2(0.5f));
                scaleLabel->color.set(bg_dark);
                scaleLabel->borderSize.set(3.0f / 1080.0f);
                scaleLabel->borderColor.set(Vector4(accent_inactive, 1.0f));
                scaleLabel->cornerRadius.set(20.0f / 1080.0f);
                scaleLabel->mouseEnterCallback = [scaleLabel, accent_active] {
                    scaleLabel->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                        scaleLabel->borderColor.get(),
                        Vector4(accent_active, 1.0f),
                        0.2f,
                        WidgetAnimationBase::COLOR,
                        [scaleLabel](const Vector4& updatedColor) {
                            scaleLabel->borderColor.set(updatedColor);
                            scaleLabel->dirty = true;
                        }));
                };
                scaleLabel->mouseLeaveCallback = [scaleLabel, accent_inactive] {
                    scaleLabel->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
                        scaleLabel->borderColor.get(),
                        Vector4(accent_inactive, 1.0f),
                        0.2f,
                        WidgetAnimationBase::COLOR,
                        [scaleLabel](const Vector4& updatedColor) {
                            scaleLabel->borderColor.set(updatedColor);
                            scaleLabel->dirty = true;
                        }));
                };

                inspector->addChild(scaleLabel);
                {
                    auto scaleText = std::make_shared<UiText>();
                    scaleText->position.set(Vector2(0.0f, 0.5f));
                    scaleText->anchorPoint.set(Vector2(0.0f, 0.5f));
                    scaleText->color.set(text);
                    scaleText->text.set(" Scale:");
                    scaleText->textSize.set(16.0f / 1080.0f);
                    scaleText->memory = sizeof(UiVertex) * 6 * scaleText->text.get().size();

                    scaleLabel->addChild(scaleText);

                    auto scaleValue = std::make_shared<UiTextBox>();
                    scaleValue->position.set(Vector2(0.35f, 0.5f));
                    scaleValue->size.set(Vector2(0.63f, 1.0f));
                    scaleValue->anchorPoint.set(Vector2(0.0f, 0.5f));
                    scaleValue->opacity.set(0.0f);
                    scaleValue->color.set(text);
                    scaleValue->textObject->text.set("");
                    scaleValue->textObject->textSize.set(15.0f / 1080.0f);
                    scaleValue->textObject->color.set(text);
                    scaleValue->memory = sizeof(UiVertex) * 6 * 24;
                    scaleValue->updateCallback = [scaleValue] {
                        if (Engine::get().scene.getSelectedObject() && !scaleValue->keyboardFocus) {
                            Vector3 scale = Engine::get().scene.getSelectedObject()->mesh->scale;
                            scaleValue->textObject->text.set(setPrecision(scale, 2));
                            scaleValue->dirty = true;
                        }
                    };
                    scaleValue->onKeyboardFocusCallback = [scaleValue] {
                        scaleValue->textObject->text.set("");
                        scaleValue->dirty = true;
                    };
                    scaleValue->onKeyboardFocusLostCallback = [scaleValue] {
                        scaleValue->dirty = true;

                        std::string input = scaleValue->textObject->text.get();
                        std::istringstream ss(input);
                        float x, y, z;
                        char comma;

                        if (!Engine::get().scene.getSelectedObject()) {
                            scaleValue->textObject->text.set("");
                            return;
                        }

                        auto obj = Engine::get().scene.getSelectedObject();

                        if (ss >> x >> comma >> y >> comma >> z) {
                            obj->mesh->scale = Vector3(x, y, z);
                        } else {
                            Vector3 scale = obj->mesh->scale;
                            scaleValue->textObject->text.set(setPrecision(scale, 2));
                        }
                    };
                    scaleLabel->addChild(scaleValue);
                }
            }
        }
    }
}