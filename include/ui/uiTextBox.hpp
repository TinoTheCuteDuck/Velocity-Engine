#pragma once

#include <ui/uiStructs.hpp>
#include <ui/uiText.hpp>
#include <ui/uiWidget.hpp>

#include <memory>

class UiTextBox : public UiWidget {
    public:
        UiTextBox();

        // Public Attributes
        WidgetAttribute<std::string> defaultText{""};

    protected:
        std::shared_ptr<UiText> textObject;

        // Internal Attributes
        bool keyboardFocus{false};

    public:
        // Public methods
        void update() override;
};