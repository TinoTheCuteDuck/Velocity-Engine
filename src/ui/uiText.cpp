// Includes
#include "math/vector/vector2.hpp"
#include <stdexcept>
#include <ui/uiText.hpp>

#include <core/engine.hpp>
#include <ui/uiWidget.hpp>

#include <functional>
#include <string>

// Public methods
void UiText::update() {
    // Update text
    if (textCallback) {
        textCallback();
    }

    // Update default UiWidget
    UiWidget::update();
}
void UiText::render() {
    // clear VertexData
    vertexData.clear();

    // Update constraints
    Vector2 windowSize = Engine::get().window.getWindowSize();
    float absoluteTextSize = textSize.get() * std::min(windowSize.x, windowSize.y);
    float characterSpacing = absoluteTextSize * 0.55f;
    absoluteSize = Vector2(characterSpacing * text.get().size(), absoluteTextSize);
    absoluteRadius = cornerRadius.get() * std::min(windowSize.x, windowSize.y);

    if (parent) {
        Vector2 absoluteParentSize = parent->getAbsoluteSize();
        Vector2 absoluteParentPosition = parent->getAbsolutePosition();
        absolutePosition = absoluteParentPosition + position.get() * absoluteParentSize;
    } else {
        absolutePosition = position.get() * windowSize;
    }

    applyConstraints();

    // Generate text quads
    for (size_t i = 0; i < text.get().size(); i++) {
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

        int character = text.get().at(i) - 32;
        int col = character % 16;
        int row = character / 16;

        float leftUV = (col * cellSize) / texSize.x;
        float rightUV = ((col + 1) * cellSize) / texSize.x;
        float topUV = (row * cellSize) / texSize.y;
        float bottomUV = ((row + 1) * cellSize) / texSize.y;

        // Generate VertexData
        Vector4 color4(color.get(), opacity.get());
        vertexData.push_back(UiVertex{Vector2(left, top), color4, Vector2(leftUV, topUV), elementID});
        vertexData.push_back(UiVertex{Vector2(left, bottom), color4, Vector2(leftUV, bottomUV), elementID});
        vertexData.push_back(UiVertex{Vector2(right, top), color4, Vector2(rightUV, topUV), elementID});

        vertexData.push_back(UiVertex{Vector2(right, top), color4, Vector2(rightUV, topUV), elementID});
        vertexData.push_back(UiVertex{Vector2(left, bottom), color4, Vector2(leftUV, bottomUV), elementID});
        vertexData.push_back(UiVertex{Vector2(right, bottom), color4, Vector2(rightUV, bottomUV), elementID});
    }

    // Reset and upload to the GPU
    vertexCount = memory / sizeof(UiVertex);
    if (vertexCount < vertexData.size())
        throw std::runtime_error("Not enough memory on the UiText");
    dirty = false;

    Vector2 flippedPos(absolutePosition.x, windowSize.y - absolutePosition.y - absoluteSize.y);
    WidgetData data = {
        Vector4(flippedPos, absoluteSize),
        borderColor.get(),
        Vector4(absoluteRadius, borderSize.get(), 0, 0)};

    Engine::get().renderer.changeGPUUiMeshData(Engine::get().uiManager.meshID, elementID, offset, memory, vertexData, data);
};
