#pragma once

#include <math/vector/vector2.hpp>
#include <math/vector/vector4.hpp>

#include <functional>

struct UiVertex {
        Vector2 position;
        Vector4 color;
        Vector2 UV;
        unsigned int widgetID;
};

struct WidgetData {
        Vector4 rect; // x, y = Position; z, w = Size;
        Vector4 borderColor;
        Vector4 params; // x = corner Radius; y = border Size; z, w = unused
};

template <typename T>
class WidgetAttribute {
    private:
        T value{};

    public:
        using Callback = std::function<void(const T&)>;

        WidgetAttribute() = default;
        WidgetAttribute(const T& initial) : value(initial) {}

        void set(const T& newValue) {
            if (value == newValue) {
                return;
            }

            value = newValue;
            if (onChanged)
                onChanged(value);
        }

        const T& get() const { return value; }

        Callback onChanged;
};