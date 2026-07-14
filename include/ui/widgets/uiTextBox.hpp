#pragma once

#include "ui/core/uiTypes.hpp"
#include "ui/widgets/uiText.hpp"
#include "ui/widgets/uiWidget.hpp"

class UiTextBox : public UiWidget {
  public:
    UiTextBox();

    WidgetAttribute<std::string> defaultText{""};
    UiText* textObject;

    bool keyboardFocus{false};

    Callback onKeyboardFocusCallback{[]() {}};
    Callback onKeyboardFocusLostCallback{[]() {}};

  public:
    void update() override;
};