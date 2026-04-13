#pragma once

#include <uiElement.hpp>

class UiText : public UiElement {
    public:
        std::string text;
        float textSize;
        UiText(const Vector2& position, const Vector3& color, const std::string& text, const float textSize);
        ~UiText() = default;
        void generateQuads(std::vector<UiVertex>& vertexData) override;
        // void update() override;
};