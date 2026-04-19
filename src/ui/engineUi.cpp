#include <engineState.hpp>
#include <engineUi.hpp>
#include <memory>
#include <uiManager.hpp>
#include <vector2.hpp>

void setupUi() {
    int width = EngineState::viewport.width;
    int height = EngineState::viewport.height;

    UiElement* leftBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(0),
        Vector2(200, height),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* topBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(0),
        Vector2(width, 150),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* rightBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(width - 200, 0),
        Vector2(200, height),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* bottomBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(0, height - 150),
        Vector2(width, 150),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* topDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(200, 150),
        Vector2(width, 4),
        Vector3(0.478, 0.635, 0.969),
        ""));

    UiElement* rightDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(width - 204, 150),
        Vector2(4, height),
        Vector3(0.478, 0.635, 0.969),
        ""));

    UiElement* leftDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(200, 150),
        Vector2(4, height),
        Vector3(0.478, 0.635, 0.969),
        ""));

    UiElement* bottomDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(200, height - 154),
        Vector2(width, 4),
        Vector3(0.478, 0.635, 0.969),
        ""));
}