#pragma once

#include <functional>
#include <string>
#include <uiElement.hpp>
#include <vector>

class UiText : public UiElement {
    public:
        std::string text;
        float textSize;
        std::function<std::string()> textProvider;
        UiText(const Vector2& position, const Vector3& color, const std::string& text, const float textSize);
        UiText(const Vector2& position, const Vector3& color, std::function<std::string()> textProvider, const float textSize);
        ~UiText() = default;
        void generateQuads(std::vector<UiVertex>& vertexData) override;
        // void update() override;
};