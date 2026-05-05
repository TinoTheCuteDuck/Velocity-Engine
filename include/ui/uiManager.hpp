#pragma once

#include <material.hpp>
#include <uiElement.hpp>

#include <memory>
#include <vector>

class UiManager {
    public:
        unsigned int meshID;
        Material material;

        UiManager();
        void load();
        void update();
        void submit();

        UiElement* addUiElement(std::unique_ptr<UiElement> element);

    private:
        void buildGeometry();

        std::vector<UiVertex> vertexData;
        std::vector<std::unique_ptr<UiElement>> uiElements;
};