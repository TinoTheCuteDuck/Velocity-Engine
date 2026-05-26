#pragma once

// Includes
#include <ui/uiStructs.hpp>
#include <ui/uiWidget.hpp>

class UiSlider : public UiWidget {
    public:
        // Public Attributes
        WidgetAttribute<Vector2> dragOffset{0.0f};

    public:
        // Callbacks
        Callback onDrag{[]() {}};
        Callback onDragEnd{[]() {}};
        Callback onDragStart{[]() {}};

    protected:
        // Private Attributes
        bool dragging{false};
        bool wasDragging{false};

    public:
        // Public Methods
        void update() override;
};