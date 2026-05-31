#pragma once

#include <functional>
#include <math/vector/vector2.hpp>
#include <math/vector/vector4.hpp>

struct UiVertex {
        Vector2 position;
        Vector4 color;
        Vector2 UV;
        unsigned int widgetID;
};

struct WidgetData {
        Vector4 rect;
        Vector4 borderColor;
        Vector4 params;
        Vector4 clipRect;
        Vector4 clipParams;
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
            if (value == newValue)
                return;

            value = newValue;
            if (onChanged)
                onChanged(value);
        }

        const T& get() const { return value; }
        Callback onChanged;
};

class WidgetAnimationBase {
    public:
        enum Channel { COLOR,
                       POSITION,
                       SCALE,
                       OPACITY,
                       ALL };
        virtual Channel getChannel() const = 0;
        virtual ~WidgetAnimationBase() = default;
        virtual bool update(float dt) = 0;
};

template <typename T>
class WidgetAnimation : public WidgetAnimationBase {
    protected:
        T startValue, endValue;
        float duration = 0.0f;
        float elapsed = 0.0f;
        Channel channel;

        std::function<void(const T&)> onChange;

    public:
        WidgetAnimation(const T& startValue, const T& endValue, float duration, Channel channel, std::function<void(const T&)> callback) : startValue(startValue), endValue(endValue), duration(duration), channel(channel), onChange(callback) {};

        bool update(float dt) override {
            elapsed += dt;
            float alpha = std::min(elapsed / duration, 1.0f);
            T finalValue = T::lerp(startValue, endValue, alpha);

            onChange(finalValue);

            return alpha >= 1.0f;
        }

        Channel getChannel() const override { return channel; }
};