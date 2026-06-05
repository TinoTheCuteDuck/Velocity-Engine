#pragma once

#include <ui/uiStructs.hpp>
#include <ui/uiText.hpp>
#include <ui/uiWidget.hpp>

class UiTextBox : public UiWidget {
  public:
    UiTextBox();

    // Public Attributes
    WidgetAttribute<std::string> defaultText{""};
    UiText* textObject;

    bool keyboardFocus{false};

    // Callbacks
    Callback onKeyboardFocusCallback{[]() {}};
    Callback onKeyboardFocusLostCallback{[]() {}};

  public:
    // Public methods
    void update() override;
};