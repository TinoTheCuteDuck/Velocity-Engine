#pragma once

#include <string>
#include <vector2.hpp>
#include <vector3.hpp>
#include <vector>

struct UiVertex {
        Vector2 position;
        Vector3 color;
        Vector2 UV;
};

class UiElement {
    public:
        Vector2 position;
        Vector2 size;
        Vector3 color;
        Vector2 UV;
        float uvWidth;
        float uvHeight;

        UiElement(const Vector2& position, const Vector2& size, const Vector3& color, const std::string& uvName);
        virtual ~UiElement() = default;
        virtual void generateQuads(std::vector<UiVertex>& vertexData);
        // virtual void update();
};