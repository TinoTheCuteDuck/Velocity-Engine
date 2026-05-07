#include <engine.hpp>

#include <engineUi.hpp>
#include <uiButton.hpp>
#include <uiElement.hpp>
#include <uiManager.hpp>
#include <uiText.hpp>

#include <input.hpp>
#include <renderer.hpp>
#include <vector2.hpp>
#include <vector3.hpp>

#include <memory>

void setupUi() {
    int width = Engine::get().window.getWindowSize().x;
    int height = Engine::get().window.getWindowSize().x;
    UiManager& manager = Engine::get().uiManager;

    UiText* fpsDisplay = static_cast<UiText*>(manager.addUiElement(std::make_unique<UiText>()));
    fpsDisplay->setPosition(Vector2(10));
    fpsDisplay->setText("FPS: 0", 32);
    fpsDisplay->setColor(1.0f);
    fpsDisplay->setUpdate([fpsDisplay]() {
        fpsDisplay->setText("FPS: " + std::to_string(Engine::get().time.getFPS()), 32);
    });

    UiText* dtDisplay = static_cast<UiText*>(manager.addUiElement(std::make_unique<UiText>()));
    dtDisplay->setPosition(Vector2(10, 42));
    dtDisplay->setText("DT: 0ms", 32);
    dtDisplay->setColor(1.0f);
    dtDisplay->setUpdate([dtDisplay]() {
        dtDisplay->setText("DT: " + std::to_string(Engine::get().time.getDt()) + "ms", 32);
    });

    UiText* wireFrameButtonLabel = static_cast<UiText*>(manager.addUiElement(std::make_unique<UiText>()));
    wireFrameButtonLabel->setPosition(Vector2((float)width / 2 - 48, 84));
    wireFrameButtonLabel->setText("Enable Wireframe", 16.0f);

    UiButton* wireFrameButton = static_cast<UiButton*>(manager.addUiElement(std::make_unique<UiButton>()));
    wireFrameButton->setPosition(Vector2((float)width / 2, 100));
    wireFrameButton->setColor(Vector3(0.8f, 0, 0));
    wireFrameButton->setSize(Vector2(40));
    wireFrameButton->setOnHover([wireFrameButton]() {
        wireFrameButton->setColor(Vector3(0, 0, 0.8f));
    });
    wireFrameButton->setOnHoverEnd([wireFrameButton]() {
        wireFrameButton->setColor(Vector3(0.8f, 0, 0));
    });
    wireFrameButton->setOnClick([]() {
        Renderer& renderer = Engine::get().renderer;
        renderer.enableWireframe(!renderer.getWireframeEnabled());
    });
    wireFrameButton->setOnHold([wireFrameButton]() {
        wireFrameButton->setPosition(Engine::get().input.getMousePos() - wireFrameButton->size / 2);
    });
    wireFrameButton->setOnHoldEnd([wireFrameButton]() {
        wireFrameButton->setColor(Vector3(0, 0, 0.8f));
    });

    UiElement* topBar = manager.addUiElement(std::make_unique<UiElement>());
    topBar->setPosition(Vector2());
    topBar->setSize(Vector2(width, 150));
    topBar->setColor(Vector3(0.102f, 0.106f, 0.149f));

    UiElement* bottomBar = manager.addUiElement(std::make_unique<UiElement>());
    bottomBar->setPosition(Vector2(0, height - 150));
    bottomBar->setSize(Vector2(width, 150));
    bottomBar->setColor(Vector3(0.102f, 0.106f, 0.149f));

    UiElement* leftBar = manager.addUiElement(std::make_unique<UiElement>());
    leftBar->setPosition(Vector2(0, 150));
    leftBar->setSize(Vector2(200, height - 300));
    leftBar->setColor(Vector3(0.102f, 0.106f, 0.149f));

    UiElement* rightBar = manager.addUiElement(std::make_unique<UiElement>());
    rightBar->setPosition(Vector2(width - 200, 150));
    rightBar->setSize(Vector2(200, height - 300));
    rightBar->setColor(Vector3(0.102f, 0.106f, 0.149f));
}