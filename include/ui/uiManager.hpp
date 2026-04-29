#pragma once

#include <material.hpp>
#include <memory>
#include <renderer.hpp>
#include <texture.hpp>
#include <uiElement.hpp>
#include <vector>

class UiManager {
    public:
        inline static unsigned int meshID;
        inline static Material material;

        static void init();
        static void update();
        static void submit();

        static UiElement* addUiElement(std::unique_ptr<UiElement> element);

    private:
        static void buildGeometry();

        inline static std::vector<UiVertex> vertexData;
        inline static std::vector<std::unique_ptr<UiElement>> uiElements;
};