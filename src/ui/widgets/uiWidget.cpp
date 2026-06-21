// Includes
#include "ui/widgets/uiWidget.hpp"

#include "core/engine.hpp"

// Public Methods
UiWidget::UiWidget() {
    Engine::get().uiManager.allocateMemory(this);
}

UiWidget::~UiWidget() {
    Engine::get().uiManager.freeMemory(elementID, offset, memory);
    vertexData.clear();
    WidgetData data{Vector4(), Vector4(), Vector4(), Vector4(), Vector4()};
    Engine::get().renderer.changeGPUUiMeshData(Engine::get().uiManager.meshID, elementID, offset, memory, vertexData, data);
}

float UiWidget::getAbsoluteRadius() const {
    return absoluteRadius;
}
float UiWidget::getAbsoluteBorderSize() const {
    return absoluteBorderSize;
}
Vector2 UiWidget::getAbsoluteSize() const {
    return absoluteSize;
}
Vector2 UiWidget::getAbsolutePosition() const {
    return absolutePosition;
}

void UiWidget::playAnimation(std::unique_ptr<WidgetAnimationBase> animation) {
    for (int i = (int) activeAnimations.size() - 1; i >= 0; i--) {
        if (animation->getChannel() == activeAnimations.at(i)->getChannel() || animation->getChannel() == WidgetAnimationBase::ALL) {
            activeAnimations.erase(activeAnimations.begin() + i);
        }
    }
    activeAnimations.push_back(std::move(animation));
}

// Event callbacks
void UiWidget::hitDetection() {
    focused = false;

    if (!enabled)
        return;

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
    float aspectRatio = aspect.get();
    if (aspectRatio > 0.0f) {
        float currentAspect = absoluteSize.x / absoluteSize.y;
        if (currentAspect > aspectRatio) {
            absoluteSize.x = absoluteSize.y * aspectRatio;
        } else {
            absoluteSize.y = absoluteSize.x / aspectRatio;
        }
    }

    Vector2 constraint = sizeConstraint.get();
    if (absoluteSize.x > constraint.x && constraint.x != 0) {
        absoluteSize.x = constraint.x;
    }
    if (absoluteSize.y > constraint.y && constraint.y != 0) {
        absoluteSize.y = constraint.y;
    }

    absolutePosition -= absoluteSize * anchorPoint.get();
}

void UiWidget::update() {
    if (!allocated) {
        Engine::get().uiManager.allocateMemory(this);
        allocated = true;
    }

    float dt = Engine::get().time.getDt();
    hitDetection();

    if (updateCallback) {
        updateCallback();
    }

    for (int i = (int) activeAnimations.size() - 1; i >= 0; i--) {
        bool finished = activeAnimations.at(i)->update(dt);
        if (finished) {
            activeAnimations.erase(activeAnimations.begin() + i);
        }
    }

    for (auto& child : children) {
        child->update();
    }

    if (dirty) {
        render(visible);
    }
}
void UiWidget::render(const bool parentVisible) {
    vertexData.clear();
    bool shouldRender = visible && parentVisible;

    if (!shouldRender) {
        WidgetData data = {Vector4(), Vector4(), Vector4(), Vector4(), Vector4()};
        Engine::get().renderer.changeGPUUiMeshData(Engine::get().uiManager.meshID, elementID, offset, memory, vertexData, data);

        for (auto& child : children) {
            child->render(false);
        }
        return;
    }

    Vector2 windowSize = Engine::get().window.getWindowSize();
    if (parent) {
        absolutePosition = parent->getAbsolutePosition() + position.get() * parent->getAbsoluteSize();
        absoluteSize = size.get() * parent->getAbsoluteSize();
    } else {
        absolutePosition = position.get() * windowSize;
        absoluteSize = size.get() * windowSize;
    }
    absoluteRadius = cornerRadius.get() * std::min(windowSize.x, windowSize.y);
    absoluteBorderSize = borderSize.get() * std::min(windowSize.x, windowSize.y);

    applyConstraints();

    float left = absolutePosition.x / windowSize.x * 2.0f - 1.0f;
    float right = (absolutePosition.x + absoluteSize.x) / windowSize.x * 2.0f - 1.0f;
    float top = -(absolutePosition.y / windowSize.y * 2.0f - 1.0f);
    float bottom = -((absolutePosition.y + absoluteSize.y) / windowSize.y * 2.0f - 1.0f);

    vertexData.push_back(UiVertex{Vector2(left, top), Vector4(color.get(), opacity.get()), Vector2(0.96875f, 0.96875f), elementID});
    vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color.get(), opacity.get()), Vector2(0.9375f, 0.96875f), elementID});
    vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color.get(), opacity.get()), Vector2(0.96875f, 0.96875f), elementID});

    vertexData.push_back(UiVertex{Vector2(right, top), Vector4(color.get(), opacity.get()), Vector2(0.96875f, 0.96875f), elementID});
    vertexData.push_back(UiVertex{Vector2(left, bottom), Vector4(color.get(), opacity.get()), Vector2(0.96875f, 0.96875f), elementID});
    vertexData.push_back(UiVertex{Vector2(right, bottom), Vector4(color.get(), opacity.get()), Vector2(0.96875f, 0.96875f), elementID});

    vertexCount = memory / sizeof(UiVertex);
    dirty = false;

    Vector2 flippedPos(absolutePosition.x, windowSize.y - absolutePosition.y - absoluteSize.y);
    WidgetData data = {
        Vector4(flippedPos, absoluteSize),
        borderColor.get(),
        Vector4(absoluteRadius, absoluteBorderSize, 0, 0),
        Vector4(0.0f),
        Vector4(0.0f)};

    if (parent && clipDescendants.get()) {
        Vector2 absoluteParentSize = parent->getAbsoluteSize();
        Vector2 absoluteParentPosition = parent->getAbsolutePosition();
        Vector2 flippedParentPos(absoluteParentPosition.x, windowSize.y - absoluteParentPosition.y - absoluteParentSize.y);
        data = {
            Vector4(flippedPos, absoluteSize),
            borderColor.get(),
            Vector4(absoluteRadius, absoluteBorderSize, 0, 0),
            Vector4(flippedParentPos, absoluteParentSize),
            Vector4(parent->getAbsoluteRadius(), parent->getAbsoluteBorderSize(), 0, 0)};
    }

    Engine::get().renderer.changeGPUUiMeshData(Engine::get().uiManager.meshID, elementID, offset, memory, vertexData, data);

    for (auto& child : children) {
        child->render(shouldRender);
    }
}