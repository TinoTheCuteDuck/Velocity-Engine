// Includes
#include <ui/uiWidget.hpp>

#include <core/engine.hpp>
#include <math/vector/vector2.hpp>

// Setters
void UiWidget::setSize(const Vector2& size, const bool lockAspect) {
    this->size = size;
    if (lockAspect) {
        Vector2 windowSize = Engine::get().window.getWindowSize();
        Vector2 pixelSize = size * windowSize;
        aspect = pixelSize.x / pixelSize.y;
    } else {
        aspect = 0.0f;
    }
}
void UiWidget::setColor(const Vector3& color) {
    this->color = color;
}
void UiWidget::setPosition(const Vector2& pos) {
    this->position = pos;
}
void UiWidget::setAnchorPoint(const Vector2& point) {
    this->anchorPoint = point;
}
void UiWidget::setBorderColor(const Vector4& color) {
    this->borderColor = color;
}
void UiWidget::setSizeConstraint(const Vector2& constraint) {
    this->sizeConstraint = constraint;
}

void UiWidget::setOpacity(const float opacity) {
    this->opacity = opacity;
}
void UiWidget::setBorderSize(const float size) {
    this->borderSize = size;
}
void UiWidget::setCornerRadius(const float radius) {
    this->cornerRadius = radius;
}

void UiWidget::setDirty(const bool state) {
    this->dirty = state;
}
void UiWidget::setEnabled(const bool state) {
    this->enabled = state;
}
void UiWidget::setVisible(const bool state) {
    this->visible = state;
}

void UiWidget::setUpdateCallback(const std::function<void()>& callback) {
    this->updateCallback = callback;
}
void UiWidget::setMouseEnterCallback(const std::function<void()>& callback) {
    this->mouseEnterCallback = callback;
}
void UiWidget::setMouseLeaveCallback(const std::function<void()>& callback) {
    this->mouseLeaveCallback = callback;
}
void UiWidget::playAnimation(const Vector2& goal, const float duration) {
    timer = 0.0f;
    animationGoal = goal;
    animationStart = position;
    animationDuration = duration;
    isPlayingAnimation = true;
}

// Getters
Vector2 UiWidget::getSize() {
    return size;
}
Vector4 UiWidget::getColor() {
    return Vector4(color, opacity);
}
Vector2 UiWidget::getPosition() {
    return position;
}

//
void onFocused();
void onFocusLost();
void UiWidget::onMouseEnter() {
    if (mouseEnterCallback) {
        mouseEnterCallback();
    }
}
void UiWidget::onMouseLeave() {
    if (mouseLeaveCallback) {
        mouseLeaveCallback();
    }
}

void UiWidget::update() {
    bool entered = false;
    float dt = Engine::get().time.getDt();
    Vector2 mousePos = Engine::get().input.getMousePos();
    Vector2 windowSize = Engine::get().window.getWindowSize();
    Vector2 absolutePosition = position * windowSize;
    Vector2 absoluteSize = size * windowSize;

    // Update
    if (updateCallback) {
        updateCallback();
    }

    // Animate
    if (isPlayingAnimation) {
        timer += dt;
        float alpha = std::min(timer / animationDuration, 1.0f);
        position = Vector2::lerp(animationStart, animationGoal, alpha);

        if (alpha >= 1.0f) {
            isPlayingAnimation = false;
            position = animationGoal;
        }
        dirty = true;
    }

    // Mouse hit detection
    if (mousePos.x >= absolutePosition.x && mousePos.x <= (absolutePosition.x + absoluteSize.x) &&
        mousePos.y >= absolutePosition.y && mousePos.y <= (absolutePosition.y + absoluteSize.y))
        entered = true;

    if (!wasEntered && entered)
        onMouseEnter();
    if (wasEntered && !entered)
        onMouseLeave();

    wasEntered = entered;

    // Renders itself and children if it's dirty
    if (dirty) {
        render();
        for (auto& child : children) {
            child->render();
        }
    }
}
void UiWidget::render() {
    // Reset vertexData
    vertexData.clear();

    Vector2 windowSize = Engine::get().window.getWindowSize();
    Vector2 absolutePosition = position * windowSize;
    Vector2 absoluteSize = size * windowSize;
    float absoluteRadius = cornerRadius * std::min(windowSize.x, windowSize.y);

    // Set Size constraint
    if (absoluteSize.x > sizeConstraint.x && sizeConstraint.x != 0) {
        absoluteSize.x = sizeConstraint.x;
    }
    if (absoluteSize.y > sizeConstraint.y && sizeConstraint.y != 0) {
        absoluteSize.y = sizeConstraint.y;
    }

    // Enforce aspect ratio
    if (aspect > 0.0f) {
        float currentAspect = absoluteSize.x / absoluteSize.y;
        if (currentAspect > aspect) {
            absoluteSize.x = absoluteSize.y * aspect;
        } else {
            absoluteSize.y = absoluteSize.x / aspect;
        }
    }

    // Apply anchorPoint
    absolutePosition -= absoluteSize * anchorPoint;

    // Convert pixel coordinates to NDC
    float left = absolutePosition.x / windowSize.x * 2.0f - 1.0f;
    float right = (absolutePosition.x + absoluteSize.x) / windowSize.x * 2.0f - 1.0f;
    float top = -(absolutePosition.y / windowSize.y * 2.0f - 1.0f);
    float bottom = -((absolutePosition.y + absoluteSize.y) / windowSize.y * 2.0f - 1.0f);

    // Generate vertex data with position, color with transparency and solid Color UVs
    vertexData.push_back(UiVertex{Vector2(left, top), Vector4(color, opacity), Vector2(0.98f, 0.02f), elementID});
    vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color, opacity), Vector2(0.98f, 0.02f), elementID});
    vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color, opacity), Vector2(0.98f, 0.02f), elementID});

    vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color, opacity), Vector2(0.98f, 0.02f), elementID});
    vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color, opacity), Vector2(0.98f, 0.02f), elementID});
    vertexData.push_back(UiVertex{Vector2(right, bottom), Vector4(color, opacity), Vector2(0.98f, 0.02f), elementID});

    // Reset and upload to the GPU
    vertexCount = vertexData.size();
    setDirty(false);

    Vector2 flippedPos(absolutePosition.x, windowSize.y - absolutePosition.y - absoluteSize.y);
    WidgetData data = {
        Vector4(flippedPos, absoluteSize),
        borderColor,
        Vector4(absoluteRadius, borderSize, 0, 0)};

    Engine::get().renderer.changeGPUUiMeshData(Engine::get().uiManager.meshID, elementID, offset, memory, vertexData, data);
}
