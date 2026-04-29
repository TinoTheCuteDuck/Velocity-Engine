#include <engineState.hpp>
#include <engineUi.hpp>
#include <memory>
#include <uiElement.hpp>
#include <uiManager.hpp>
#include <uiText.hpp>
#include <vector2.hpp>

void setupUi() {
    int width = EngineState::viewport.width;
    int height = EngineState::viewport.height;

    UiElement* topBar = UiManager::addUiElement(std::make_unique<UiElement>());
    topBar->setPosition(Vector2());
    topBar->setSize(Vector2(width, 150));
    topBar->setColor(Vector3(0.102f, 0.106f, 0.149f));

    UiElement* bottomBar = UiManager::addUiElement(std::make_unique<UiElement>());
    bottomBar->setPosition(Vector2(0, height - 150));
    bottomBar->setSize(Vector2(width, 150));
    bottomBar->setColor(Vector3(0.102f, 0.106f, 0.149f));

    UiElement* leftBar = UiManager::addUiElement(std::make_unique<UiElement>());
    leftBar->setPosition(Vector2(0, 150));
    leftBar->setSize(Vector2(200, height - 300));
    leftBar->setColor(Vector3(0.102f, 0.106f, 0.149f));

    UiElement* rightBar = UiManager::addUiElement(std::make_unique<UiElement>());
    rightBar->setPosition(Vector2(width - 200, 150));
    rightBar->setSize(Vector2(200, height - 300));
    rightBar->setColor(Vector3(0.102f, 0.106f, 0.149f));

    UiText* fpsDisplay = static_cast<UiText*>(UiManager::addUiElement(std::make_unique<UiText>()));
    fpsDisplay->setPosition(Vector2(300, 400));
    fpsDisplay->setText("FPS: 0", 32);
    fpsDisplay->setColor(1.0f);
    fpsDisplay->setUpdate([fpsDisplay]() {
        fpsDisplay->setText("FPS: " + std::to_string(EngineState::frame.FPS), 32);
    });

    UiText* dtDisplay = static_cast<UiText*>(UiManager::addUiElement(std::make_unique<UiText>()));
    dtDisplay->setPosition(Vector2(300, 432));
    dtDisplay->setText("DT: 0ms", 32);
    dtDisplay->setColor(1.0f);
    dtDisplay->setUpdate([dtDisplay]() {
        dtDisplay->setText("DT: " + std::to_string(EngineState::frame.dt) + "ms", 32);
    });
}