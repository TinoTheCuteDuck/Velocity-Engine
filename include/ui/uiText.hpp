#pragma once

#include <ui/uiWidget.hpp>

#include <functional>
#include <string>

class UiText : public UiWidget {
    public:
        // Setters
        void setText(const std::string& text, const float textSize);
        void setTextCallback(const std::function<void()>& callback);

    protected:
        // Attributes
        std::string text = "";
        float textSize = 0.00833f;

        // Callbacks
        std::function<void()> textCallback = []() {};

    public:
        // Public Methods
        void update() override;
        void render() override;
};