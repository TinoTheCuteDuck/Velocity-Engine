// Includes
#include <ui/uiText.hpp>

#include <core/engine.hpp>
#include <ui/uiWidget.hpp>

#include <functional>
#include <string>

// Setters
void UiText::setText(const std::string& text, const float textSize) {
    this->text = text;
    this->textSize = textSize;
}
void UiText::setTextCallback(const std::function<void()>& callback) {
    this->textCallback = callback;
}

// Public methods
void UiText::update() {
    // Update text
    if (textCallback) {
        textCallback();
        setDirty(true);
    }

    // Update default UiWidget
    UiWidget::update();
}
void UiText::render() {
    // clear VertexData
    vertexData.clear();

    // Update constraints
    Vector2 windowSize = Engine::get().window.getWindowSize();
    float absoluteTextSize = textSize * std::min(windowSize.x, windowSize.y);
    float characterSpacing = absoluteTextSize * 0.55f;

    absolutePosition = position * windowSize;
    absoluteSize = Vector2(characterSpacing * text.size(), absoluteTextSize);
    absoluteRadius = cornerRadius * std::min(windowSize.x, windowSize.y);

    applyConstraints();

    // Generate text quads
    for (size_t i = 0; i < text.size(); i++) {
        // Convert pixel coordinates to NDC
        float x = absolutePosition.x + i * characterSpacing;
        float y = absolutePosition.y;

        float left = (x / windowSize.x) * 2.0f - 1.0f;
        float right = ((x + absoluteTextSize) / windowSize.x) * 2.0f - 1.0f;
        float top = -((y / windowSize.y) * 2.0f - 1.0f);
        float bottom = -(((y + absoluteTextSize) / windowSize.y) * 2.0f - 1.0f);

        // Generate UVs
        float cellSize = 72.0f;
        Vector2 texSize(1152.0f, 432.0f);

        int character = text.at(i) - 32;
        int col = character % 16;
        int row = character / 16;

        float leftUV = (col * cellSize) / texSize.x;
        float rightUV = ((col + 1) * cellSize) / texSize.x;
        float topUV = (row * cellSize) / texSize.y;
        float bottomUV = ((row + 1) * cellSize) / texSize.y;

        // Generate VertexData
        vertexData.push_back(UiVertex{Vector2(left, top), Vector4(color, opacity), Vector2(leftUV, topUV), elementID});
        vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color, opacity), Vector2(leftUV, bottomUV), elementID});
        vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color, opacity), Vector2(rightUV, topUV), elementID});

        vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color, opacity), Vector2(rightUV, topUV), elementID});
        vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color, opacity), Vector2(leftUV, bottomUV), elementID});
        vertexData.push_back(UiVertex{Vector2(right, bottom), Vector4(color, opacity), Vector2(rightUV, bottomUV), elementID});
    }

    // Reset and upload to the GPU
    vertexCount = memory / sizeof(UiVertex);
    setDirty(false);

    Vector2 flippedPos(absolutePosition.x, windowSize.y - absolutePosition.y - absoluteSize.y);
    WidgetData data = {
        Vector4(flippedPos, absoluteSize),
        borderColor,
        Vector4(absoluteRadius, borderSize, 0, 0)};

    Engine::get().renderer.changeGPUUiMeshData(Engine::get().uiManager.meshID, elementID, offset, memory, vertexData, data);
};
