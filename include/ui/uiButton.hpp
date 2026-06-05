#pragma once

#include <functional>
#include <ui/uiWidget.hpp>

using Callback = std::function<void()>;

class UiButton : public UiWidget {
  public:
    // Callbacks
    Callback onMouseButton1Up{[]() {}};
    Callback onMouseButton1Down{[]() {}};
    Callback onMouseButton1Click{[]() {}};

    Callback onMouseButton2Up{[]() {}};
    Callback onMouseButton2Down{[]() {}};
    Callback onMouseButton2Click{[]() {}};

  public:
    // Public Methods
    void update() override;
};