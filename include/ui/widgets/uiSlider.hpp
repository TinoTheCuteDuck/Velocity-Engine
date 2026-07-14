#pragma once

#include "ui/core/uiTypes.hpp"
#include "ui/widgets/uiWidget.hpp"

class UiSlider : public UiWidget {
  public:
    WidgetAttribute<Vector2> dragOffset{0.0f};

  public:
    Callback onDrag{[]() {}};
    Callback onDragEnd{[]() {}};
    Callback onDragStart{[]() {}};

  protected:
    bool dragging{false};
    bool wasDragging{false};

  public:
    void update() override;
};