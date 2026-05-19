#pragma once

// Includes
#include <math/vector/vector2.hpp>
#include <math/vector/vector3.hpp>
#include <math/vector/vector4.hpp>

#include <functional>
#include <vector>

struct UiVertex {
        Vector2 position;
        Vector4 color;
        Vector2 UV;
};

// Default UiWidget everything inherits from.
class UiWidget {
    public:
        // Constructor and Destructor
        UiWidget();
        virtual ~UiWidget();

        // Setters
        void setSize(const Vector2& size);
        void setColor(const Vector3& color);
        void setPosition(const Vector2& pos);
        void setBorderColor(const Vector4& color);

        void setOpacity(const float opacity);
        void setBorderSize(const float size);
        void setCornerRadius(const float radius);

        void setDirty(const bool state);
        void setEnabled(const bool state);
        void setVisible(const bool state);

        void setMouseEnterCallback(const std::function<void()>& callback);
        void setMouseLeaveCallback(const std::function<void()>& callback);

    public:
        // Public attributes
        UiWidget* parent = nullptr;
        std::vector<UiWidget*> children;

        size_t memory = sizeof(UiVertex) * 6;
        size_t offset = 0;
        size_t vertexCount = 6;

    protected:
        // Attributes
        Vector2 size = Vector2(100.0f);
        Vector3 color = Vector3(1.0f);
        Vector2 position = Vector2(0.0f);
        Vector4 borderColor = Vector4(0.0f);

        float opacity = 1.0f;
        float borderSize = 0.0f;
        float cornerRadius = 0.0f;

        bool dirty = true;
        bool enabled = true;
        bool visible = true;
        bool wasEntered = false;

    protected:
        // Event Callbacks
        std::function<void()> mouseEnterCallback;
        std::function<void()> mouseLeaveCallback;

    public:
        // Public Methods
        virtual void update();
        virtual void render();

    private:
        // Private methods
        virtual void onFocused();
        virtual void onFocusLost();
        virtual void onMouseEnter();
        virtual void onMouseLeave();
};