#pragma once

#include <functional>
#include <uiElement.hpp>

class UiButton : public UiElement {
    public:
        UiButton();
        void update() override;

        void setOnClick(const std::function<void()>& callback);
        void setOnHover(const std::function<void()>& callback);
        void setOnHoverEnd(const std::function<void()>& callback);
        void setOnHold(const std::function<void()>& callback);
        void setOnHoldEnd(const std::function<void()>& callback);

    public:
        bool isHeld = false;
        bool isPressed = false;
        bool isHovered = false;
        bool wasHovered = false;
        bool wasHeld = false;

    private:
        std::function<void()> onClick = []() {};
        std::function<void()> onHover = []() {};
        std::function<void()> onHoverEnd = []() {};
        std::function<void()> onHold = []() {};
        std::function<void()> onHoldEnd = []() {};
};