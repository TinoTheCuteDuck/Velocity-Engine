#pragma once

#include "math/vector/vector3.hpp"

#include <functional>
#include <string>

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

class MeshInstance {
  public:
    MeshInstance(const std::string& filePath) : filePath(filePath) {}

  public:
    std::string filePath;

    MeshAttribute<Vector3> color{Vector3(1)};
    MeshAttribute<float> opacity{1};
};