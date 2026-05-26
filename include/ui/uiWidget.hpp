#pragma once

// Includes
#include <math/vector/vector2.hpp>
#include <math/vector/vector3.hpp>
#include <math/vector/vector4.hpp>

#include <ui/uiStructs.hpp>

#include <functional>
#include <memory>
#include <vector>

using Callback = std::function<void()>;

// Default UiWidget everything inherits from.
class UiWidget {
    public:
        // Constructor and Destructor
        UiWidget() = default;
        virtual ~UiWidget() = default;

        // Read-only getters
        float getAbsoluteRadius() const;
        Vector2 getAbsoluteSize() const;
        Vector2 getAbsolutePosition() const;

        void addChild(std::shared_ptr<UiWidget> child);
        void playAnimation(const Vector2& goal, const float duration);

    public:
        // Public Attributes
        UiWidget* parent{nullptr};
        std::vector<std::shared_ptr<UiWidget>> children;

        unsigned int elementID{0};
        size_t memory{sizeof(UiVertex) * 6};
        size_t offset{0};
        size_t vertexCount{6};

    public:
        // Attributes
        WidgetAttribute<Vector2> size{0.1f};
        WidgetAttribute<Vector3> color{1.0f};
        WidgetAttribute<Vector2> position{0.0f};
        WidgetAttribute<Vector2> anchorPoint{0.0f};
        WidgetAttribute<Vector4> borderColor{0.0f};
        WidgetAttribute<Vector2> sizeConstraint{0.0f};

        WidgetAttribute<float> aspect{0.0f};
        WidgetAttribute<float> opacity{1.0f};
        WidgetAttribute<float> borderSize{0.0f};
        WidgetAttribute<float> cornerRadius{0.0f};

        bool dirty{true};
        bool enabled{true};
        bool visible{true};

    public:
        // Event Callbacks
        Callback updateCallback{[]() {}};
        Callback mouseEnterCallback{[]() {}};
        Callback mouseLeaveCallback{[]() {}};

    protected:
        // Internal Attributes
        Vector2 animationGoal{};
        Vector2 animationStart{};

        Vector2 absoluteSize{};
        Vector2 absolutePosition{};
        float absoluteRadius{0.0f};

        float timer{0.0f};
        float animationDuration{0.0f};
        bool isPlayingAnimation{false};

        bool focused{false};
        bool wasFocused{false};

        std::vector<UiVertex> vertexData;

    public:
        // Public Methods
        virtual void update();
        virtual void render();

    protected:
        // Private Methods
        // virtual void onFocused();
        // virtual void onFocusLost();
        void hitDetection();
        void applyConstraints();
};