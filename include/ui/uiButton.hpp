#pragma once

#include <uiElement.hpp>

class UiButton : public UiElement {
    public:
        UiButton();
        bool isPressed();
        bool isHovered();
};