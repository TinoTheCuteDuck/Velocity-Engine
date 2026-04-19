#include <engineState.hpp>
#include <uiElement.hpp>

UiElement::UiElement(const Vector2& position, const Vector2& size, const Vector3& color, const std::string& uvName) : position(position), size(size), color(color), UV(Vector2()), uvWidth(0), uvHeight(0) {
}

void UiElement::generateQuads(std::vector<UiVertex>& vertexData) {
    int width = EngineState::viewport.width;
    int height = EngineState::viewport.height;

    float leftX = (position.x / width) * 2 - 1;
    float rightX = ((position.x + size.x) / width) * 2 - 1;
    float topY = -((position.y / height) * 2 - 1);
    float bottomY = -(((position.y + size.y) / height) * 2 - 1);

    float uvLeft = UV.x;
    float uvRight = UV.x + uvWidth;
    float uvTop = UV.y;
    float uvBottom = UV.y + uvHeight;

    vertexData.push_back(UiVertex{Vector2(leftX, bottomY), color, Vector2(uvLeft, uvBottom)});
    vertexData.push_back(UiVertex{Vector2(rightX, bottomY), color, Vector2(uvRight, uvBottom)});
    vertexData.push_back(UiVertex{Vector2(leftX, topY), color, Vector2(uvLeft, uvTop)});

    vertexData.push_back(UiVertex{Vector2(rightX, bottomY), color, Vector2(uvRight, uvBottom)});
    vertexData.push_back(UiVertex{Vector2(rightX, topY), color, Vector2(uvRight, uvTop)});
    vertexData.push_back(UiVertex{Vector2(leftX, topY), color, Vector2(uvLeft, uvTop)});
}