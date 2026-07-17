#pragma once

#include "ui/core/uiTypes.hpp"
#include "ui/widgets/uiWidget.hpp"

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
    void render(bool parentVisible) override;
};