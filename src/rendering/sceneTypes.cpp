#include "rendering/sceneTypes.hpp"

#include "core/engine.hpp"
#include "rendering/renderingTypes.hpp"

DirectionalLight::DirectionalLight(const unsigned int componentId, const Vector3& direction, const Vector3& color, const float intensity) {
    this->componentId = componentId;

    this->direction.set(direction);
    this->direction.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->color.set(color);
    this->color.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->intensity.set(intensity);
    this->intensity.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    changeGPUData();
}

DirectionalLight::DirectionalLight(DirectionalLight&& other) noexcept {
    componentId = other.componentId;

    direction = other.direction;
    color = other.color;
    intensity = other.intensity;

    direction.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    color.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    intensity.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };

    other.componentId = 0;
}
DirectionalLight::~DirectionalLight() {
    if (componentId != 0) {
        constexpr GPUDirectionalLight light{.direction = Vector4(), .color = Vector4()};
        Engine::get().renderer.changeDirectionalLightUBO(componentId, light);
    }
}

void DirectionalLight::changeGPUData() const {
    const GPUDirectionalLight light{.direction = Vector4(direction.get(), 0), .color = Vector4(color.get(), intensity.get())};
    Engine::get().renderer.changeDirectionalLightUBO(componentId, light);
}

PointLight::PointLight(const unsigned int componentId, const Vector3& position, const Vector3& color, const float intensity, const float constant, const float linear, const float quadratic) {
    this->componentId = componentId;

    this->position.set(position);
    this->position.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->color.set(color);
    this->color.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };

    this->intensity.set(intensity);
    this->intensity.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->constant.set(constant);
    this->constant.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->linear.set(linear);
    this->linear.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->quadratic.set(quadratic);
    this->quadratic.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    changeGPUData();
}

PointLight::PointLight(PointLight&& other) noexcept {
    componentId = other.componentId;

    position = other.position;
    color = other.color;

    intensity = other.intensity;
    constant = other.constant;
    linear = other.linear;
    quadratic = other.linear;

    this->position.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->color.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->intensity.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->constant.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->linear.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->quadratic.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };

    other.componentId = 0;
}

PointLight::~PointLight() {
    if (componentId != 0) {
        constexpr GPUPointLight light{.position = Vector4(), .color = Vector4(), .params = Vector4()};
        Engine::get().renderer.changePointLightUBO(componentId, light);
    }
}

void PointLight::changeGPUData() const {
    const GPUPointLight light{.position = Vector4(position.get(), 0), .color = Vector4(color.get(), 0), .params = Vector4(intensity.get(), constant.get(), linear.get(), quadratic.get())};
    Engine::get().renderer.changePointLightUBO(componentId, light);
}

SpotLight::SpotLight(const unsigned int componentId, const Vector3& position, const Vector3& direction, const Vector3& color, const float intensity, const float outerAngle, const float innerAngle, const float constant, const float linear, const float quadratic) {
    this->componentId = componentId;

    this->position.set(position);
    this->position.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->direction.set(direction);
    this->direction.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->color.set(color);
    this->color.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };

    this->intensity.set(intensity);
    this->intensity.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->outerAngle.set(outerAngle);
    this->outerAngle.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->innerAngle.set(innerAngle);
    this->innerAngle.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };

    this->constant.set(constant);
    this->constant.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->linear.set(linear);
    this->linear.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->quadratic.set(quadratic);
    this->quadratic.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };

    changeGPUData();
}

SpotLight::SpotLight(SpotLight&& other) noexcept {
    componentId = other.componentId;

    position = other.position;
    direction = other.direction;
    color = other.color;

    intensity = other.intensity;
    outerAngle = other.outerAngle;
    innerAngle = other.innerAngle;

    constant = other.constant;
    linear = other.linear;
    quadratic = other.quadratic;

    this->position.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->direction.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->color.onChanged = [this]([[maybe_unused]] const Vector3& newValue) {
        this->changeGPUData();
    };
    this->intensity.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->outerAngle.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->innerAngle.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };

    this->constant.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->linear.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };
    this->quadratic.onChanged = [this]([[maybe_unused]] const float newValue) {
        this->changeGPUData();
    };

    other.componentId = 0;
}

SpotLight::~SpotLight() {
    constexpr GPUSpotLight light{.position = Vector4(), .direction = Vector4(), .color = Vector4(), .params = Vector4(), .attenuationParams = Vector4()};
    Engine::get().renderer.changeSpotLightUBO(componentId, light);
}

void SpotLight::changeGPUData() const {
    const GPUSpotLight light{.position = Vector4(position.get(), 0), .direction = Vector4(direction.get(), 0), .color = Vector4(color.get(), 0), .params = Vector4(intensity.get(), outerAngle.get(), innerAngle.get(), 0), .attenuationParams = Vector4(constant.get(), linear.get(), quadratic.get(), 0)};
    Engine::get().renderer.changeSpotLightUBO(componentId, light);
}