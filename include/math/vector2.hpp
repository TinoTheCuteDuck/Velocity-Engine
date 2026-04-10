#pragma once

#include <assert.h>
#include <cmath>
#include <iostream>

class Vector2 {
    public:
        float x, y;

        constexpr Vector2() : x(0.0f), y(0.0f) {};
        constexpr Vector2(const float xy) : x(xy), y(xy) {};
        constexpr Vector2(const float x, const float y) : x(x), y(y) {};

        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 up;
        static const Vector2 right;

        inline constexpr Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        inline constexpr Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        inline constexpr Vector2& operator+=(const float scalar) {
            x += scalar;
            y += scalar;
            return *this;
        }
        inline constexpr Vector2& operator-=(const float scalar) {
            x -= scalar;
            y -= scalar;
            return *this;
        }
        inline constexpr Vector2& operator*=(const float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        inline constexpr Vector2& operator/=(const float scalar) {
            assert(scalar != 0);
            x /= scalar;
            y /= scalar;
            return *this;
        }

        inline constexpr Vector2 operator+(const Vector2& other) const {
            return Vector2(
                x + other.x,
                y + other.y);
        }
        inline constexpr Vector2 operator-(const Vector2& other) const {
            return Vector2(
                x - other.x,
                y - other.y);
        }

        inline constexpr Vector2 operator+(const float scalar) const {
            return Vector2(
                x + scalar,
                y + scalar);
        }
        inline constexpr Vector2 operator-(const float scalar) const {
            return Vector2(
                x - scalar,
                y - scalar);
        }
        inline constexpr Vector2 operator*(const float scalar) const {
            return Vector2(
                x * scalar,
                y * scalar);
        }
        inline constexpr Vector2 operator/(const float scalar) const {
            assert(scalar != 0);
            return Vector2(
                x / scalar,
                y / scalar);
        }

        inline friend constexpr Vector2 operator+(const float scalar, const Vector2& vec) {
            return Vector2(
                vec.x + scalar,
                vec.y + scalar);
        }
        inline friend constexpr Vector2 operator-(const float scalar, const Vector2& vec) {
            return Vector2(
                vec.x - scalar,
                vec.y - scalar);
        }
        inline friend constexpr Vector2 operator*(const float scalar, const Vector2& vec) {
            return Vector2(
                vec.x * scalar,
                vec.y * scalar);
        }

        inline constexpr Vector2 operator-() const {
            return Vector2(-x, -y);
        }
        inline friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
            os << "(" << vec.x << ", " << vec.y << ")";
            return os;
        }

        inline constexpr bool operator==(const Vector2& other) const {
            return std::abs(x - other.x) < 1e-6f && std::abs(y - other.y) < 1e-6f;
        }
        inline constexpr bool operator!=(const Vector2& other) const {
            return !(*this == other);
        }

        inline constexpr float length() const {
            return std::sqrt(x * x + y * y);
        }
        inline constexpr float lengthSqr() const {
            return x * x + y * y;
        }
        inline constexpr float dot(const Vector2& other) const {
            return x * other.x + y * other.y;
        }
        inline constexpr float distance(const Vector2& other) const {
            return (*this - other).length();
        }
        inline constexpr float distanceSqr(const Vector2& other) const {
            return (*this - other).lengthSqr();
        }
        inline constexpr Vector2 normalize() const {
            float len = length();
            assert(len != 0);
            return Vector2(
                x / len,
                y / len);
        }
};

inline constexpr Vector2 Vector2::zero = Vector2();
inline constexpr Vector2 Vector2::one = Vector2(1.0f);
inline constexpr Vector2 Vector2::up = Vector2(0.0f, 1.0f);
inline constexpr Vector2 Vector2::right = Vector2(1.0f, 0.0f);