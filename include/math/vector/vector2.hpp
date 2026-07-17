#pragma once

#include <cmath>
#include <iostream>

class Vector2 {
  public:
    float x, y;

    constexpr Vector2() : x(0.0f), y(0.0f) {};
    explicit constexpr Vector2(const float xy) : x(xy), y(xy) {};
    constexpr Vector2(const float x, const float y) : x(x), y(y) {};

    static const Vector2 zero;
    static const Vector2 one;
    static const Vector2 up;
    static const Vector2 right;

    constexpr Vector2 &operator+=(const Vector2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    constexpr Vector2 &operator-=(const Vector2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr Vector2 &operator+=(const float scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }
    constexpr Vector2 &operator-=(const float scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }
    constexpr Vector2 &operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    constexpr Vector2 &operator/=(const float scalar) {
        if (scalar == 0.0f) return *this;

        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr Vector2 operator+(const Vector2 &other) const {
        return {
            x + other.x,
            y + other.y};
    }
    constexpr Vector2 operator-(const Vector2 &other) const {
        return {
            x - other.x,
            y - other.y};
    }
    constexpr Vector2 operator*(const Vector2 &other) const {
        return {
            x * other.x,
            y * other.y};
    }

    constexpr Vector2 operator+(const float scalar) const {
        return {
            x + scalar,
            y + scalar};
    }
    constexpr Vector2 operator-(const float scalar) const {
        return {
            x - scalar,
            y - scalar};
    }
    constexpr Vector2 operator*(const float scalar) const {
        return {
            x * scalar,
            y * scalar};
    }
    constexpr Vector2 operator/(const float scalar) const {
        if (scalar == 0.0f) return *this;

        return {
            x / scalar,
            y / scalar};
    }

    friend constexpr Vector2 operator+(const float scalar, const Vector2 &vec) {
        return {
            vec.x + scalar,
            vec.y + scalar};
    }
    friend constexpr Vector2 operator-(const float scalar, const Vector2 &vec) {
        return {
            vec.x - scalar,
            vec.y - scalar};
    }
    friend constexpr Vector2 operator*(const float scalar, const Vector2 &vec) {
        return {
            vec.x * scalar,
            vec.y * scalar};
    }

    constexpr Vector2 operator-() const {
        return {-x, -y};
    }
    friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    constexpr bool operator==(const Vector2 &other) const {
        return std::abs(x - other.x) < 1e-6f && std::abs(y - other.y) < 1e-6f;
    }
    constexpr bool operator!=(const Vector2 &other) const {
        return !(*this == other);
    }

    [[nodiscard]] constexpr float length() const {
        return std::sqrt(x * x + y * y);
    }
    [[nodiscard]] constexpr float lengthSqr() const {
        return x * x + y * y;
    }
    [[nodiscard]] constexpr float dot(const Vector2 &other) const {
        return x * other.x + y * other.y;
    }
    [[nodiscard]] constexpr float distance(const Vector2 &other) const {
        return (*this - other).length();
    }
    [[nodiscard]] constexpr float distanceSqr(const Vector2 &other) const {
        return (*this - other).lengthSqr();
    }
    [[nodiscard]] constexpr Vector2 normalize() const {
        const float len = length();
        if (len == 0.0f) return *this;

        return {
            x / len,
            y / len};
    }

    static constexpr Vector2 lerp(const Vector2 &a, const Vector2 &b, const float t) {
        return (1.0f - t) * a + t * b;
    }
};

constexpr Vector2 Vector2::zero = Vector2();
constexpr Vector2 Vector2::one = Vector2(1.0f);
constexpr Vector2 Vector2::up = Vector2(0.0f, 1.0f);
constexpr Vector2 Vector2::right = Vector2(1.0f, 0.0f);