#include <engineState.hpp>
#include <uiElement.hpp>

void UiElement::generateQuads(std::vector<UiVertex>& vertexData) {
    const int width = EngineState::viewport.width;
    const int height = EngineState::viewport.height;

    float leftX = (position.x / width) * 2 - 1;
    float rightX = ((position.x + size.x) / width) * 2 - 1;
    float topY = -((position.y / height) * 2 - 1);
    float bottomY = -(((position.y + size.y) / height) * 2 - 1);

    float uvLeft = 0.98f;
    float uvRight = 0.99f;
    float uvTop = 0.98f;
    float uvBottom = 0.99f;

    vertexData.push_back(UiVertex{Vector2(leftX, bottomY), color, Vector2(uvLeft, uvBottom)});
    vertexData.push_back(UiVertex{Vector2(rightX, bottomY), color, Vector2(uvRight, uvBottom)});
    vertexData.push_back(UiVertex{Vector2(leftX, topY), color, Vector2(uvLeft, uvTop)});

    vertexData.push_back(UiVertex{Vector2(rightX, bottomY), color, Vector2(uvRight, uvBottom)});
    vertexData.push_back(UiVertex{Vector2(rightX, topY), color, Vector2(uvRight, uvTop)});
    vertexData.push_back(UiVertex{Vector2(leftX, topY), color, Vector2(uvLeft, uvTop)});
}

void UiElement::update() {
    updateCallback();
}

void UiElement::setPosition(const Vector2 position) {
    this->position = position;
}

void UiElement::setSize(const Vector2 size) {
    this->size = size;
}

void UiElement::setColor(const Vector3 color) {
    this->color = color;
}

void UiElement::setUV(const Vector2 UV) {
    this->UV = UV;
}

void UiElement::setUpdate(const std::function<void()>& updateCallback) {
    this->updateCallback = updateCallback;
}