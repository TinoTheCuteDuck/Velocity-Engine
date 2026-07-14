#pragma once

#include "math/matrices/mat4.hpp"
#include "math/vector/vector2.hpp"
#include "math/vector/vector3.hpp"
#include "math/vector/vector4.hpp"

#include <functional>
#include <optional>

struct Material {
    std::string vertexPath;
    std::string fragmentPath;

    std::string albedo;
};

struct RenderCall {
    unsigned int meshID;
    unsigned int meshComponentID;
    Material material;
    std::optional<Mat4> transform = std::nullopt;
    std::optional<bool> depthTest = true;
};

struct LightRenderCall {
    Vector3 lightDirection;

    std::string vertexPath;
    std::string fragmentPath;
};

struct BoundingBox {
    Vector3 min;
    Vector3 max;

    Vector3& operator[](int index) {
        return (index == 0) ? min : max;
    }
};

struct Vertex {
    Vector3 position;
    Vector2 UV;
    Vector3 normal;
};

struct VertexKey {
    int v;
    int vt;
    int vn;

    bool operator==(const VertexKey& other) const {
        return v == other.v &&
               vt == other.vt &&
               vn == other.vn;
    }
};

namespace std {
template <>
struct hash<VertexKey> {
    size_t operator()(const VertexKey& k) const {
        return (k.v * 73856093) ^ (k.vt * 19349663) ^ (k.vn * 83492791);
    }
};
}  // namespace std

template <typename T>
class MeshAttribute {
  public:
    using Callback = std::function<void(const T&)>;

    MeshAttribute() = default;
    MeshAttribute(T initialValue) : value(initialValue) {}

    void set(T newValue) {
        if (value == newValue)
            return;

        value = newValue;
        if (onChanged) {
            onChanged(value);
        }
    }

    const T& get() const { return value; }
    Callback onChanged;

  private:
    T value{};
};

struct CameraMatrices {
    Mat4 viewProjection;
    Vector4 viewPos;
};

struct MeshInstanceData {
    Vector4 color;
};

struct GPUDirectionalLight {
    Vector4 direction;  // w unused
    Vector4 color;      // w is intensity
};

struct GPUPointLight {
    Vector4 position;  // w unused
    Vector4 color;     // w unused
    Vector4 params;    // x = intensity, y = constant, z = linear, w = quadratic
};

struct GPUSpotLight {
    Vector4 position;           // w unused
    Vector4 direction;          // w unused
    Vector4 color;              // w unused
    Vector4 params;             // x = intensity, y = outerAngle, z = innerAngle, w = unused
    Vector4 attenuationParams;  // x = constant, y = linear, z = quadratic, w = unused
};