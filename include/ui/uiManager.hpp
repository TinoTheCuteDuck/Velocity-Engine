#pragma once

#include <memory>
#include <texture.hpp>
#include <uiElement.hpp>
#include <vector2.hpp>
#include <vector3.hpp>
#include <vector>

class UiManager {
    public:
        static void init();
        static void addUiElement(std::unique_ptr<UiElement> element);
        static void buildUiMesh();
        static void draw();

    private:
        static std::vector<std::unique_ptr<UiElement>> uiElements;
        static unsigned int VAO, VBO;
        static std::unique_ptr<Texture> uiTexture;
        static int vertexSize;
};