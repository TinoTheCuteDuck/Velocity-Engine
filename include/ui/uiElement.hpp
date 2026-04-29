#pragma once

#include <functional>
#include <vector2.hpp>
#include <vector3.hpp>
#include <vector>

struct UiVertex {
        Vector2 position;
        Vector3 color;
        Vector2 UV;
};

class UiElement {
    protected:
        Vector2 position;
        Vector2 size;
        Vector3 color;
        Vector2 UV;

        std::function<void()> updateCallback = []() {};

    public:
        inline UiElement() : position(0.0f), size(100.0f), color(0.8f), UV(0, 0) {};
        virtual ~UiElement() = default;
        virtual void generateQuads(std::vector<UiVertex>& vertexData);

        void update();
        void setPosition(const Vector2 position);
        void setSize(const Vector2 size);
        void setColor(const Vector3 color);
        void setUV(const Vector2 UV);
        void setUpdate(const std::function<void()>& callback);
};