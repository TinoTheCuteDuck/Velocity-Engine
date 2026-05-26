#pragma once

#include <ui/uiStructs.hpp>
#include <ui/uiWidget.hpp>

#include <string>

class UiText : public UiWidget {
    public:
        // Public Attributes
        WidgetAttribute<std::string> text{""};
        WidgetAttribute<float> textSize{0.029629f};

    public:
        // Callbacks
        Callback textCallback{[]() {}};

    public:
        // Public Methods
        void update() override;
        void render() override;
};