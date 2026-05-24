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
        unsigned int widgetID;
};

struct WidgetData {
        Vector4 rect; // x, y = Position; z, w = Size;
        Vector4 borderColor;
        Vector4 params; // x = corner Radius; y = border Size; z, w = unused
};

// Default UiWidget everything inherits from.
class UiWidget {
    public:
        // Constructor and Destructor
        UiWidget() = default;
        virtual ~UiWidget() = default;

        // Setters
        void setSize(const Vector2& size, const bool lockAspect);
        void setColor(const Vector3& color);
        void setPosition(const Vector2& pos);
        void setAnchorPoint(const Vector2& point);
        void setBorderColor(const Vector4& color);
        void setSizeConstraint(const Vector2& constraint);

        void setOpacity(const float opacity);
        void setBorderSize(const float size);
        void setCornerRadius(const float radius);

        void setDirty(const bool state);
        void setEnabled(const bool state);
        void setVisible(const bool state);

        void setUpdateCallback(const std::function<void()>& callback);
        void setMouseEnterCallback(const std::function<void()>& callback);
        void setMouseLeaveCallback(const std::function<void()>& callback);

        void playAnimation(const Vector2& goal, const float duration);

        // Getters
        Vector2 getSize();
        Vector4 getColor();
        Vector2 getPosition();

    public:
        // Public attributes
        UiWidget* parent = nullptr;
        std::vector<UiWidget*> children;

        unsigned int elementID = 0;
        size_t memory = sizeof(UiVertex) * 6;
        size_t offset = 0;
        size_t vertexCount = 6;

    protected:
        // Attributes
        Vector2 size = Vector2(100.0f);
        Vector3 color = Vector3(1.0f);
        Vector2 position = Vector2(0.0f);
        Vector2 anchorPoint = Vector2(0.0f);
        Vector4 borderColor = Vector4(0.0f);
        Vector2 sizeConstraint = Vector2(0.0f, 0.0f);

        float aspect = 0.0f;
        float opacity = 1.0f;
        float borderSize = 0.0f;
        float cornerRadius = 0.0f;

        bool dirty = true;
        bool enabled = true;
        bool visible = true;
        bool wasEntered = false;

        // Internal Attributes
        Vector2 animationGoal = Vector2();
        Vector2 animationStart = Vector2();

        float timer = 0.0f;
        float animationDuration = 0.0f;
        bool isPlayingAnimation = false;

        std::vector<UiVertex> vertexData;

    protected:
        // Event Callbacks
        std::function<void()> updateCallback;
        std::function<void()> mouseEnterCallback;
        std::function<void()> mouseLeaveCallback;

    public:
        // Public Methods
        virtual void update();
        virtual void render();

    private:
        // Private methods
        // virtual void onFocused();
        // virtual void onFocusLost();
        virtual void onMouseEnter();
        virtual void onMouseLeave();
};