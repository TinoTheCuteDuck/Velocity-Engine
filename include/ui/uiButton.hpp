#pragma once

#include <uiElement.hpp>

class UiButton : public UiElement {
    public:
        UiButton();
        void onClick();
        void generateQuads(std::vector<UiVertex>& vertexData) override;
        // void update() override;
};