#pragma once

#include "math/vector/vector2.hpp"
#include "math/vector/vector3.hpp"
#include "math/vector/vector4.hpp"
#include "ui/core/uiTypes.hpp"

#include <functional>
#include <memory>
#include <vector>

using Callback = std::function<void()>;

// Default UiWidget everything inherits from.
class UiWidget {
  public:
    // Constructor and Destructor
    UiWidget();
    virtual ~UiWidget();

    // Read-only getters
    float getAbsoluteRadius() const;
    float getAbsoluteBorderSize() const;
    Vector2 getAbsoluteSize() const;
    Vector2 getAbsolutePosition() const;

    template <typename T>
    void addChild(std::unique_ptr<T> child) {
        static_assert(std::is_base_of_v<UiWidget, T>, "T must derive from UiWidget");
        child->parent = this;
        children.push_back(std::move(child));
    }

    void playAnimation(std::unique_ptr<WidgetAnimationBase> animation);

  public:
    // Public Attributes
    UiWidget* parent{nullptr};
    std::vector<std::unique_ptr<UiWidget>> children;

    unsigned int elementID{0};
    size_t memory{sizeof(UiVertex) * 6};
    size_t offset{0};
    size_t vertexCount{6};

    bool focused{false};
    bool wasFocused{false};

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

    WidgetAttribute<bool> clipDescendants{true};

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
    bool allocated{false};

    Vector2 absoluteSize{};
    Vector2 absolutePosition{};
    float absoluteRadius{0.0f};
    float absoluteBorderSize{0.0f};

    std::vector<UiVertex> vertexData;
    std::vector<std::unique_ptr<WidgetAnimationBase>> activeAnimations;

  public:
    // Public Methods
    virtual void update();
    virtual void render(const bool parentVisible);

  protected:
    // Private Methods
    // virtual void onFocused();
    // virtual void onFocusLost();
    void hitDetection();
    void applyConstraints();
};