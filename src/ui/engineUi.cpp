#include <engineContext.hpp>
#include <engineUi.hpp>
#include <memory>
#include <uiManager.hpp>
#include <vector2.hpp>

void setupUi() {
    UiElement* leftBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(0),
        Vector2(200, gEngineContext.height),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* topBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(0),
        Vector2(gEngineContext.width, 150),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* rightBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(gEngineContext.width - 200, 0),
        Vector2(200, gEngineContext.height),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* bottomBar = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(0, gEngineContext.height - 150),
        Vector2(gEngineContext.width, 150),
        Vector3(0.102, 0.106, 0.149),
        ""));

    UiElement* topDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(200, 150),
        Vector2(gEngineContext.width, 4),
        Vector3(0.478, 0.635, 0.969),
        ""));

    UiElement* rightDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(gEngineContext.width - 204, 150),
        Vector2(4, gEngineContext.height),
        Vector3(0.478, 0.635, 0.969),
        ""));

    UiElement* leftDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(200, 150),
        Vector2(4, gEngineContext.height),
        Vector3(0.478, 0.635, 0.969),
        ""));

    UiElement* bottomDeco = UiManager::addStaticElement(std::make_unique<UiElement>(
        Vector2(200, gEngineContext.height - 154),
        Vector2(gEngineContext.width, 4),
        Vector3(0.478, 0.635, 0.969),
        ""));
}