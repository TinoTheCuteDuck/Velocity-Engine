// Includes
#include <memory>
#include <ui/uiStructs.hpp>
#include <ui/uiWidget.hpp>

#include <core/engine.hpp>
#include <math/vector/vector2.hpp>

// Public Methods
float UiWidget::getAbsoluteRadius() const {
    return absoluteRadius;
}
Vector2 UiWidget::getAbsoluteSize() const {
    return absoluteSize;
}
Vector2 UiWidget::getAbsolutePosition() const {
    return absolutePosition;
}

void UiWidget::addChild(std::shared_ptr<UiWidget> child) {
    child->parent = this;
    children.push_back(std::move(child));
}
void UiWidget::playAnimation(const Vector2& goal, const float duration) {
    timer = 0.0f;
    animationGoal = goal;
    animationStart = position.get();
    animationDuration = duration;
    isPlayingAnimation = true;
}

// Event callbacks
void UiWidget::hitDetection() {
    focused = false;

    Input& input = Engine::get().input;
    Vector2 mousePos = input.getMousePos();

    // Mouse hit detection
    if (mousePos.x >= absolutePosition.x && mousePos.x <= (absolutePosition.x + absoluteSize.x) &&
        mousePos.y >= absolutePosition.y && mousePos.y <= (absolutePosition.y + absoluteSize.y))
        focused = true;

    if (!wasFocused && focused)
        mouseEnterCallback();
    if (wasFocused && !focused)
        mouseLeaveCallback();

    wasFocused = focused;
}
void UiWidget::applyConstraints() {
    // Enforce aspect ratio
    float aspectRatio = aspect.get();
    if (aspectRatio > 0.0f) {
        float currentAspect = absoluteSize.x / absoluteSize.y;
        if (currentAspect > aspectRatio) {
            absoluteSize.x = absoluteSize.y * aspectRatio;
        } else {
            absoluteSize.y = absoluteSize.x / aspectRatio;
        }
    }

    // Apply size constraint
    Vector2 constraint = sizeConstraint.get();
    if (absoluteSize.x > constraint.x && constraint.x != 0) {
        absoluteSize.x = constraint.x;
    }
    if (absoluteSize.y > constraint.y && constraint.y != 0) {
        absoluteSize.y = constraint.y;
    }

    // Apply anchorPoint
    absolutePosition -= absoluteSize * anchorPoint.get();
}

void UiWidget::update() {
    float dt = Engine::get().time.getDt();
    hitDetection();

    // Update
    if (updateCallback) {
        updateCallback();
    }

    // Animate
    if (isPlayingAnimation) {
        timer += dt;
        float alpha = std::min(timer / animationDuration, 1.0f);
        position.set(Vector2::lerp(animationStart, animationGoal, alpha));

        if (alpha >= 1.0f) {
            isPlayingAnimation = false;
            position.set(animationGoal);
        }
        dirty = true;
    }

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

    // Update constraints
    Vector2 windowSize = Engine::get().window.getWindowSize();
    if (parent) {
        absolutePosition = parent->getAbsolutePosition() + position.get() * parent->getAbsoluteSize();
        absoluteSize = size.get() * parent->getAbsoluteSize();
    } else {
        absolutePosition = position.get() * windowSize;
        absoluteSize = size.get() * windowSize;
    }
    absoluteRadius = cornerRadius.get() * std::min(windowSize.x, windowSize.y);

    applyConstraints();

    // Convert pixel coordinates to NDC
    float left = absolutePosition.x / windowSize.x * 2.0f - 1.0f;
    float right = (absolutePosition.x + absoluteSize.x) / windowSize.x * 2.0f - 1.0f;
    float top = -(absolutePosition.y / windowSize.y * 2.0f - 1.0f);
    float bottom = -((absolutePosition.y + absoluteSize.y) / windowSize.y * 2.0f - 1.0f);

    // Generate vertex data with position, color with transparency and solid Color UVs
    vertexData.push_back(UiVertex{Vector2(left, top), Vector4(color.get(), opacity.get()), Vector2(0.9375f, 0.833f), elementID});
    vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color.get(), opacity.get()), Vector2(0.9375f, 1.0f), elementID});
    vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color.get(), opacity.get()), Vector2(1.0f, 0.833f), elementID});

    vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color.get(), opacity.get()), Vector2(1.0f, 0.833f), elementID});
    vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color.get(), opacity.get()), Vector2(0.9375f, 1.0f), elementID});
    vertexData.push_back(UiVertex{Vector2(right, bottom), Vector4(color.get(), opacity.get()), Vector2(1.0f, 1.0f), elementID});

    // Reset and upload to the GPU
    vertexCount = memory / sizeof(UiVertex);
    dirty = false;

    Vector2 flippedPos(absolutePosition.x, windowSize.y - absolutePosition.y - absoluteSize.y);
    WidgetData data = {
        Vector4(flippedPos, absoluteSize),
        borderColor.get(),
        Vector4(absoluteRadius, borderSize.get(), 0, 0)};

    Engine::get().renderer.changeGPUUiMeshData(Engine::get().uiManager.meshID, elementID, offset, memory, vertexData, data);
}
