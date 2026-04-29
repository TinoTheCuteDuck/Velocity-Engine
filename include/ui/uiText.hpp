#pragma once

#include <string>
#include <uiElement.hpp>
#include <vector>

class UiText : public UiElement {
    private:
        std::string text;
        float textSize;

    public:
        inline UiText() : text(""), textSize(0.0f) {};
        ~UiText() = default;

        void generateQuads(std::vector<UiVertex>& vertexData) override;
        void setText(const std::string& text, float textSize = 16.0f);
};