#pragma once

#include "math/vector/vector3.hpp"

#include <cmath>
#include <iostream>

class Vector4 {
  public:
    float x, y, z, w;

    constexpr Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
    explicit constexpr Vector4(const float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {};
    constexpr Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {};
    constexpr Vector4(const Vector2 &vec1, const Vector2 &vec2) : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) {};
    constexpr Vector4(const Vector3 &vec, const float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {};

    static const Vector4 zero;
    static const Vector4 one;
    static const Vector4 up;
    static const Vector4 right;
    static const Vector4 forward;

    constexpr Vector4 &operator+=(const Vector4 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }
    constexpr Vector4 &operator-=(const Vector4 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    constexpr Vector4 &operator+=(const float scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }
    constexpr Vector4 &operator-=(const float scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }
    constexpr Vector4 &operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }
    constexpr Vector4 &operator/=(const float scalar) {
        if (scalar == 0.0f) return *this;

        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    constexpr Vector4 operator+(const Vector4 &other) const {
        return {
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w};
    }
    constexpr Vector4 operator-(const Vector4 &other) const {
        return {
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w};
    }
    constexpr Vector4 operator*(const Vector4 &other) const {
        return {
            x * other.x,
            y * other.y,
            z * other.z,
            w * other.w};
    }

    constexpr Vector4 operator+(const float scalar) const {
        return {
            x + scalar,
            y + scalar,
            z + scalar,
            w + scalar};
    }
    constexpr Vector4 operator-(const float scalar) const {
        return {
            x - scalar,
            y - scalar,
            z - scalar,
            w - scalar};
    }
    constexpr Vector4 operator*(const float scalar) const {
        return {
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar};
    }
    constexpr Vector4 operator/(const float scalar) const {
        if (scalar == 0.0f) return *this;

        return {
            x / scalar,
            y / scalar,
            z / scalar,
            w / scalar};
    }

    friend constexpr Vector4 operator+(const float scalar, const Vector4 &vec) {
        return {
            vec.x + scalar,
            vec.y + scalar,
            vec.z + scalar,
            vec.w + scalar};
    }
    friend constexpr Vector4 operator-(const float scalar, const Vector4 &vec) {
        return {
            vec.x - scalar,
            vec.y - scalar,
            vec.z - scalar,
            vec.w - scalar};
    }
    friend constexpr Vector4 operator*(const float scalar, const Vector4 &vec) {
        return {
            vec.x * scalar,
            vec.y * scalar,
            vec.z * scalar,
            vec.w * scalar};
    }

    constexpr Vector4 operator-() const {
        return {-x, -y, -z, -w};
    }
    friend std::ostream &operator<<(std::ostream &os, const Vector4 &vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        return os;
    }

    constexpr bool operator==(const Vector4 &other) const {
        return std::abs(x - other.x) < 1e-6f && std::abs(y - other.y) < 1e-6f && std::abs(z - other.z) < 1e-6f && std::abs(w - other.w) < 1e-6f;
    }
    constexpr bool operator!=(const Vector4 &other) const {
        return !(*this == other);
    }

    [[nodiscard]] constexpr float length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    [[nodiscard]] constexpr float lengthSqr() const {
        return x * x + y * y + z * z + w * w;
    }
    [[nodiscard]] constexpr float dot(const Vector4 &other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    [[nodiscard]] constexpr float distance(const Vector4 &other) const {
        return (*this - other).length();
    }
    [[nodiscard]] constexpr float distanceSqr(const Vector4 &other) const {
        return (*this - other).lengthSqr();
    }
    [[nodiscard]] constexpr Vector4 normalize() const {
        const float len = length();
        if (len == 0.0f) return *this;

        return {
            x / len,
            y / len,
            z / len,
            w / len};
    }
    static constexpr Vector4 lerp(const Vector4 &a, const Vector4 &b, const float t) {
        return (1.0f - t) * a + t * b;
    }
};

constexpr Vector4 Vector4::zero = Vector4();
constexpr Vector4 Vector4::one = Vector4(1.0f);
constexpr Vector4 Vector4::up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
constexpr Vector4 Vector4::right = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
constexpr Vector4 Vector4::forward = Vector4(0.0f, 0.0f, -1.0f, 0.0f);