#pragma once

#include <memory>
#include <uiElement.hpp>
#include <vector>

class UiManager {
    public:
        static void init();
        static void update();
        static void submit();
        static void shutdown();

        static UiElement* addStaticElement(std::unique_ptr<UiElement> element);
        static UiElement* addDynamicElement(std::unique_ptr<UiElement> element);
        static UiElement* addStaticText(std::unique_ptr<UiElement> element);
        static UiElement* addDynamicText(std::unique_ptr<UiElement> element);

    private:
        static void initBuffer(unsigned int& VAO, unsigned int& VBO);
        static void buildBuffer(unsigned int VAO, unsigned int VBO, std::vector<UiVertex>& vertexData);
        static void buildGeometry(std::vector<std::unique_ptr<UiElement>>& elements, std::vector<UiVertex>& vertexData);

        static bool staticElementsDirty;
        static bool dynamicElementsDirty;
        static bool staticTextDirty;
        static bool dynamicTextDirty;

        static unsigned int staticElementsVAO, staticElementsVBO;
        static unsigned int dynamicElementsVAO, dynamicElementsVBO;
        static unsigned int staticTextVAO, staticTextVBO;
        static unsigned int dynamicTextVAO, dynamicTextVBO;

        static std::vector<UiVertex> staticElementsVertexData;
        static std::vector<UiVertex> dynamicElementsVertexData;
        static std::vector<UiVertex> staticTextVertexData;
        static std::vector<UiVertex> dynamicTextVertexData;

        static std::vector<std::unique_ptr<UiElement>> staticElements;
        static std::vector<std::unique_ptr<UiElement>> dynamicElements;
        static std::vector<std::unique_ptr<UiElement>> staticText;
        static std::vector<std::unique_ptr<UiElement>> dynamicText;
};