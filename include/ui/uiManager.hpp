#pragma once

#include <core/engineContext.hpp>
#include <math/vector2.hpp>
#include <math/vector3.hpp>
#include <vector>

struct UiElement {
        Vector2 position;
        Vector2 size;
        Vector3 color;
        Vector2 UV;
};

struct UiVertex {
        Vector2 position;
        Vector3 color;
        Vector2 UV;
};

class UiManager {
    public:
        UiManager();
        ~UiManager();
        void addUiElement(const Vector2& position, const Vector2& size, const Vector3& color, const Vector2& UV);
        void generateUiMesh();
        void draw();
        void clear();

    private:
        std::vector<UiElement> uiElements;
        unsigned int VAO, VBO;
        unsigned int texture;
        unsigned int vertexCount;
};