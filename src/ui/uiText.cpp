#include <engineContext.hpp>
#include <uiText.hpp>

UiText::UiText(const Vector2& position, const Vector3& color, const std::string& text, const float textSize) : UiElement(position, Vector2(), color, ""), text(text), textSize(textSize) {
}
UiText::UiText(const Vector2& position, const Vector3& color, std::function<std::string()> textProvider, const float textSize) : UiElement(position, Vector2(), color, ""), textProvider(textProvider), textSize(textSize) {
}

void UiText::generateQuads(std::vector<UiVertex>& vertexData) {
    if (textProvider) {
        text = textProvider();
    }
    for (int i = 0; i < text.size(); i++) {
        float leftX = ((position.x + i * textSize) / gEngineContext.width) * 2 - 1;
        float rightX = ((position.x + i * textSize + textSize) / gEngineContext.width) * 2 - 1;
        float topY = -((position.y / gEngineContext.height) * 2 - 1);
        float bottomY = -(((position.y + textSize) / gEngineContext.height) * 2 - 1);

        int index = (unsigned int)text[i] - 32;
        int col = index % 10;
        int row = index / 10;

        float uvLeft = col / 10.0f;
        float uvRight = (col + 1) / 10.0f;
        float uvTop = row / 10.0f;
        float uvBottom = (row + 1) / 10.0f;

        vertexData.push_back(UiVertex{Vector2(leftX, bottomY), color, Vector2(uvLeft, uvBottom)});
        vertexData.push_back(UiVertex{Vector2(rightX, bottomY), color, Vector2(uvRight, uvBottom)});
        vertexData.push_back(UiVertex{Vector2(leftX, topY), color, Vector2(uvLeft, uvTop)});

        vertexData.push_back(UiVertex{Vector2(rightX, bottomY), color, Vector2(uvRight, uvBottom)});
        vertexData.push_back(UiVertex{Vector2(rightX, topY), color, Vector2(uvRight, uvTop)});
        vertexData.push_back(UiVertex{Vector2(leftX, topY), color, Vector2(uvLeft, uvTop)});
    }
}