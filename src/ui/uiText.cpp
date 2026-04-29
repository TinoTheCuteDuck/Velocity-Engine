#include <engineState.hpp>
#include <uiText.hpp>

void UiText::generateQuads(std::vector<UiVertex>& vertexData) {
    int width = EngineState::viewport.width;
    int height = EngineState::viewport.height;
    float charSpacing = textSize * 0.5f;

    for (int i = 0; i < (int)text.size(); i++) {
        float leftX = ((position.x + i * charSpacing) / width) * 2 - 1;
        float rightX = ((position.x + i * charSpacing + textSize) / width) * 2 - 1;
        float topY = -((position.y / height) * 2 - 1);
        float bottomY = -(((position.y + textSize) / height) * 2 - 1);

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

void UiText::setText(const std::string& text, float textSize) {
    this->text = text;
    this->textSize = textSize;
}