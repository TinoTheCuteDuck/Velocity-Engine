#pragma once

#include <GLFW/glfw3.h>
#include <core/engine.hpp>
#include <iomanip>
#include <math/vector/vector2.hpp>
#include <memory>
#include <rendering/scene.hpp>
#include <sstream>
#include <string>
#include <ui/uiButton.hpp>
#include <ui/uiManager.hpp>
#include <ui/uiSlider.hpp>
#include <ui/uiStructs.hpp>
#include <ui/uiText.hpp>
#include <ui/uiTextBox.hpp>
#include <ui/uiWidget.hpp>

namespace Colors {
inline Vector3 background_dark(26.0f / 255.0f, 27.0f / 255.0f, 38.0f / 255.0f);
inline Vector3 background_main(45.0f / 255.0f, 47.0f / 255.0f, 65.0f / 255.0f);
inline Vector3 foreground(192.0f / 255.0f, 202.0f / 255.0f, 245.0f / 255.0f);
inline Vector3 accent_active(122.0f / 255.0f, 162.0f / 255.0f, 247.0f / 255.0f);
inline Vector3 accent_inactive(65.0f / 255.0f, 72.0f / 255.0f, 104.0f / 255.0f);
// inline Vector3 tertiary(40.0f / 255.0f, 52.0f / 255.0f, 87.0f / 255.0f);
}  // namespace Colors

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

inline std::shared_ptr<UiWidget> createScaleProperty() {
    auto container = std::make_shared<UiWidget>();
    container->position.set(Vector2(0.5f, 0.21825f));
    container->size.set(Vector2(0.96f, 0.045f));
    container->anchorPoint.set(Vector2(0.5f));
    container->color.set(Colors::background_dark);
    container->borderSize.set(3.0f / 1080.0f);
    container->borderColor.set(Vector4(Colors::accent_inactive, 1.0f));
    container->cornerRadius.set(20.0f / 1080.0f);
    container->mouseEnterCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_active, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->mouseLeaveCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_inactive, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };

    auto text = std::make_shared<UiText>();
    text->position.set(Vector2(0.0f, 0.5f));
    text->anchorPoint.set(Vector2(0.0f, 0.5f));
    text->color.set(Colors::foreground);
    text->text.set(" Scale:");
    text->textSize.set(16.0f / 1080.0f);
    text->memory = sizeof(UiVertex) * 6 * text->text.get().size();

    auto value = std::make_shared<UiTextBox>();
    value->position.set(Vector2(0.35f, 0.5f));
    value->size.set(Vector2(0.63f, 1.0f));
    value->anchorPoint.set(Vector2(0.0f, 0.5f));
    value->opacity.set(0.0f);
    value->textObject->text.set("");
    value->textObject->textSize.set(15.0f / 1080.0f);
    value->textObject->color.set(Colors::foreground);
    value->memory = sizeof(UiVertex) * 6 * 24;
    value->updateCallback = [value] {
        unsigned int id = Engine::get().scene.getSelectedEntity();
        if (id > 0 && !value->keyboardFocus) {
            Vector3 scale = Engine::get().scene.transforms.at(id).scale;
            value->textObject->text.set(setPrecision(scale, 2));
            value->dirty = true;
        }
    };
    value->onKeyboardFocusCallback = [value] {
        value->textObject->text.set("");
        value->dirty = true;
    };
    value->onKeyboardFocusLostCallback = [value] {
        value->dirty = true;

        std::string input = value->textObject->text.get();
        std::istringstream ss(input);
        float x, y, z;
        char comma;

        Scene& scene = Engine::get().scene;
        unsigned int entityID = Engine::get().scene.getSelectedEntity();

        if (entityID == 0) {
            value->textObject->text.set("");
            return;
        }

        if (ss >> x >> comma >> y >> comma >> z) {
            scene.transforms.at(entityID).scale = Vector3(x, y, z);
        } else {
            Vector3 scale = scene.transforms.at(entityID).scale;
            value->textObject->text.set(setPrecision(scale, 2));
        }
    };

    container->addChild(text);
    container->addChild(value);

    return container;
}

inline std::shared_ptr<UiWidget> createColorProperty() {
    auto container = std::make_shared<UiWidget>();
    container->position.set(Vector2(0.5f, 0.165f));
    container->size.set(Vector2(0.96f, 0.045f));
    container->anchorPoint.set(Vector2(0.5f));
    container->color.set(Colors::background_dark);
    container->borderSize.set(3.0f / 1080.0f);
    container->borderColor.set(Vector4(Colors::accent_inactive, 1.0f));
    container->cornerRadius.set(20.0f / 1080.0f);
    container->mouseEnterCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_active, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->mouseLeaveCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_inactive, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };

    auto text = std::make_shared<UiText>();
    text->position.set(Vector2(0.0f, 0.5f));
    text->anchorPoint.set(Vector2(0.0f, 0.5f));
    text->color.set(Colors::foreground);
    text->text.set(" Color:");
    text->textSize.set(16.0f / 1080.0f);
    text->memory = sizeof(UiVertex) * 6 * text->text.get().size();

    auto value = std::make_shared<UiTextBox>();
    value->position.set(Vector2(0.35f, 0.5f));
    value->size.set(Vector2(0.63f, 1.0f));
    value->anchorPoint.set(Vector2(0.0f, 0.5f));
    value->opacity.set(0.0f);
    value->textObject->text.set("");
    value->textObject->textSize.set(15.0f / 1080.0f);
    value->textObject->color.set(Colors::foreground);
    value->memory = sizeof(UiVertex) * 6 * 24;
    value->updateCallback = [value] {
        unsigned int id = Engine::get().scene.getSelectedEntity();
        if (id > 0 && !value->keyboardFocus) {
            Vector3 color = Engine::get().scene.meshes.at(id).color * 255;
            value->textObject->text.set(setPrecision(color, 0));
            value->dirty = true;
        }
    };
    value->onKeyboardFocusCallback = [value] {
        value->textObject->text.set("");
        value->dirty = true;
    };
    value->onKeyboardFocusLostCallback = [value] {
        value->dirty = true;

        std::string input = value->textObject->text.get();
        std::istringstream ss(input);
        float x, y, z;
        char comma;

        Scene& scene = Engine::get().scene;
        unsigned int entityID = Engine::get().scene.getSelectedEntity();

        if (entityID == 0) {
            value->textObject->text.set("");
            return;
        }

        if (ss >> x >> comma >> y >> comma >> z) {
            scene.meshes.at(entityID).color = Vector3(x, y, z) / 255;
        } else {
            Vector3 color = scene.meshes.at(entityID).color * 255;
            value->textObject->text.set(setPrecision(color, 0));
        }
    };

    container->addChild(text);
    container->addChild(value);

    return container;
}

inline std::shared_ptr<UiWidget> createPositionProperty() {
    auto container = std::make_shared<UiWidget>();
    container->position.set(Vector2(0.5f, 0.112f));
    container->size.set(Vector2(0.96f, 0.045f));
    container->anchorPoint.set(Vector2(0.5f));
    container->color.set(Colors::background_dark);
    container->borderSize.set(3.0f / 1080.0f);
    container->borderColor.set(Vector4(Colors::accent_inactive, 1.0f));
    container->cornerRadius.set(20.0f / 1080.0f);
    container->mouseEnterCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_active, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->mouseLeaveCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_inactive, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };

    auto text = std::make_shared<UiText>();
    text->position.set(Vector2(0.0f, 0.5f));
    text->anchorPoint.set(Vector2(0.0f, 0.5f));
    text->color.set(Colors::foreground);
    text->text.set(" Position:");
    text->textSize.set(16.0f / 1080.0f);
    text->memory = sizeof(UiVertex) * 6 * text->text.get().size();

    auto value = std::make_shared<UiTextBox>();
    value->position.set(Vector2(0.4f, 0.5f));
    value->size.set(Vector2(0.58f, 1.0f));
    value->anchorPoint.set(Vector2(0.0f, 0.5f));
    value->opacity.set(0.0f);
    value->textObject->text.set("");
    value->textObject->textSize.set(15.0f / 1080.0f);
    value->textObject->color.set(Colors::foreground);
    value->memory = sizeof(UiVertex) * 6 * 24;
    value->updateCallback = [value] {
        unsigned int id = Engine::get().scene.getSelectedEntity();
        if (id > 0 && !value->keyboardFocus) {
            Vector3 position = Engine::get().scene.transforms.at(id).position;
            value->textObject->text.set(setPrecision(position, 2));
            value->dirty = true;
        }
    };
    value->onKeyboardFocusCallback = [value] {
        value->textObject->text.set("");
        value->dirty = true;
    };
    value->onKeyboardFocusLostCallback = [value] {
        value->dirty = true;

        std::string input = value->textObject->text.get();
        std::istringstream ss(input);
        float x, y, z;
        char comma;

        Scene& scene = Engine::get().scene;
        unsigned int entityID = Engine::get().scene.getSelectedEntity();

        if (entityID == 0) {
            value->textObject->text.set("");
            return;
        }

        if (ss >> x >> comma >> y >> comma >> z) {
            scene.transforms.at(entityID).position = Vector3(x, y, z);

        } else {
            value->textObject->text.set(setPrecision(scene.transforms.at(entityID).position, 2));
        }
    };

    container->addChild(text);
    container->addChild(value);

    return container;
}

inline std::shared_ptr<UiWidget> createInspectorHeader() {
    auto container = std::make_shared<UiWidget>();
    container->position.set(Vector2(0.0f));
    container->size.set(Vector2(1.0f, 70.0f / 1080.0f));
    container->color.set(Colors::background_dark);

    auto text = std::make_shared<UiText>();
    text->position.set(Vector2(0.5f));
    text->anchorPoint.set(Vector2(0.5f));
    text->text.set("Properties");
    text->color.set(Colors::foreground);
    text->textSize.set(32.0f / 1080.0f);
    text->memory = sizeof(UiVertex) * 6 * text->text.get().size();

    container->addChild(text);

    return container;
}

inline void createInspector(UiManager& manager) {
    auto container = manager.addUiWidget<UiWidget>();
    container->position.set(Vector2(-0.3f, 580.0f / 1080.0f));
    container->anchorPoint.set(Vector2(0.5f));
    container->size.set(Vector2(250.0f / 1920.0f, 940.0f / 1080.0f));
    container->cornerRadius.set(60.0f / 1080.0f);
    container->color.set(Colors::background_main);
    container->borderColor.set(Vector4(Colors::accent_active, 1.0f));
    container->borderSize.set(4.0f / 1080.0f);
    container->mouseEnterCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_active, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->mouseLeaveCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_inactive, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->updateCallback = [container] {
        static Vector2 inspectorTarget = Vector2(-0.3f, 580.0f / 1080.0f);

        Vector2 newTarget = Engine::get().scene.getSelectedEntity() > 0
                                ? Vector2(155.0f / 1920.0f, 580.0f / 1080.0f)
                                : Vector2(-0.3f, 580.0f / 1080.0f);

        if (newTarget != inspectorTarget) {
            inspectorTarget = newTarget;

            container->playAnimation(std::make_unique<WidgetAnimation<Vector2>>(
                container->position.get(),
                newTarget,
                0.3f,
                WidgetAnimationBase::POSITION,
                [container](const Vector2& updatedPosition) {
                    container->position.set(updatedPosition);
                    container->dirty = true;
                }));
        }
    };

    container->addChild(createInspectorHeader());
    container->addChild(createPositionProperty());
    container->addChild(createColorProperty());
    container->addChild(createScaleProperty());
}

inline std::shared_ptr<UiWidget> createEntityEmblem() {
    auto container = std::make_shared<UiButton>();
    container->position.set(Vector2(0.5f, 0.112f));
    container->size.set(Vector2(0.96f, 0.045f));
    container->anchorPoint.set(Vector2(0.5f));
    container->color.set(Colors::background_dark);
    container->borderSize.set(3.0f / 1080.0f);
    container->borderColor.set(Vector4(Colors::accent_inactive, 1.0f));
    container->cornerRadius.set(20.0f / 1080.0f);
    container->mouseEnterCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_active, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->mouseLeaveCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_inactive, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };

    return container;
}

inline void createSceneHierarchy(UiManager& manager) {
    auto container = manager.addUiWidget<UiWidget>();
    container->position.set(Vector2(1765.0f / 1920.0f, 580.0f / 1080.0f));
    container->anchorPoint.set(Vector2(0.5f));
    container->size.set(Vector2(250.0f / 1920.0f, 940.0f / 1080.0f));
    container->cornerRadius.set(60.0f / 1080.0f);
    container->color.set(Colors::background_main);
    container->borderColor.set(Vector4(Colors::accent_active, 1.0f));
    container->borderSize.set(4.0f / 1080.0f);
    container->mouseEnterCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_active, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->mouseLeaveCallback = [container] {
        container->playAnimation(std::make_unique<WidgetAnimation<Vector4>>(
            container->borderColor.get(),
            Vector4(Colors::accent_inactive, 1.0f),
            0.2f,
            WidgetAnimationBase::COLOR,
            [container](const Vector4& updatedColor) {
                container->borderColor.set(updatedColor);
                container->dirty = true;
            }));
    };
    container->updateCallback = [container] {
        static size_t lastSize = 0;
        size_t newSize = Engine::get().scene.entities.size();
        if (newSize != lastSize) {
            lastSize = newSize;
            container->children.clear();

            for (auto [index, id] : Engine::get().scene.entities) {
                (void) index;
                (void) id;
            }
        }
    };
}

inline void loadUi() {
    UiManager& manager = Engine::get().uiManager;
    createInspector(manager);
    createSceneHierarchy(manager);
}