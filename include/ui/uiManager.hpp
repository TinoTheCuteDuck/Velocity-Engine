#pragma once

#include <material.hpp>
#include <uiElement.hpp>

#include <memory>
#include <vector>

class UiManager {
    public:
        static UiManager& get();
        static void setInstance(UiManager& uiManager);

        unsigned int meshID;
        Material material;

        UiManager();
        void load();
        void update();
        void submit();

        UiElement* addUiElement(std::unique_ptr<UiElement> element);

    private:
        inline static UiManager* instance = nullptr;
        void buildGeometry();

        std::vector<UiVertex> vertexData;
        std::vector<std::unique_ptr<UiElement>> uiElements;
};