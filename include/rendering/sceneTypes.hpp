#pragma once

#include "math/matrices/mat4.hpp"
#include "math/vector/vector3.hpp"

#include <functional>

struct Transform {
    Transform(Vector3& position, Vector3& scale, Vector3 rotation) : position(position), scale(scale), rotation(rotation) {}

    Vector3 position;
    Vector3 scale;
    Vector3 rotation;

    Mat4 getMatrice() {
        return Mat4::translate(position) * Mat4::scale(scale);
    }
};

template <typename T>
class Attribute {
  public:
    using Callback = std::function<void(T newValue)>;

    Attribute() = default;
    Attribute(T initialValue) : value(initialValue) {}

    void set(T newValue) {
        if (value == newValue)
            return;

        value = newValue;
        if (onChanged)
            onChanged(newValue);
    }

    const T& get() const { return value; }
    Callback onChanged;

  private:
    T value{};
};

class DirectionalLight {
  public:
    DirectionalLight(const unsigned int componentId, const Vector3& direction, const Vector3& color, const float intensity);
    DirectionalLight(DirectionalLight&& other) noexcept;
    ~DirectionalLight();

  public:
    unsigned int componentId;

    Attribute<Vector3> direction;
    Attribute<Vector3> color;
    Attribute<float> intensity;

  private:
    void changeGPUData();
};

class PointLight {
  public:
    PointLight(const unsigned int componentId, const Vector3& position, const Vector3& color, const float intensity, const float constant, const float linear, const float quadratic);
    PointLight(PointLight&& other) noexcept;
    ~PointLight();

  public:
    unsigned int componentId;

    Attribute<Vector3> position;
    Attribute<Vector3> color;

    Attribute<float> intensity;
    Attribute<float> constant;
    Attribute<float> linear;
    Attribute<float> quadratic;

  private:
    void changeGPUData();
};

class SpotLight {
  public:
    SpotLight(const unsigned int componentId, const Vector3& position, const Vector3& direction, const Vector3& color, const float intensity, const float outerAngle, const float innerAngle, const float constant, const float linear, const float quadratic);
    SpotLight(SpotLight&& other) noexcept;
    ~SpotLight();

  public:
    unsigned int componentId;

    Attribute<Vector3> position;
    Attribute<Vector3> direction;
    Attribute<Vector3> color;

    Attribute<float> intensity;
    Attribute<float> outerAngle;
    Attribute<float> innerAngle;

    Attribute<float> constant;
    Attribute<float> linear;
    Attribute<float> quadratic;

  private:
    void changeGPUData();
};