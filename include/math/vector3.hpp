#pragma once

#include <assert.h>
#include <cmath>
#include <iostream>
#include <math/vector2.hpp>

class Vector3 {
    public:
        float x, y, z;

        constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {};
        constexpr Vector3(const float xyz) : x(xyz), y(xyz), z(xyz) {};
        constexpr Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {};
        constexpr Vector3(const Vector2& vec, const float z) : x(vec.x), y(vec.y), z(z) {};

        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 up;
        static const Vector3 right;
        static const Vector3 forward;

        inline constexpr Vector3& operator+=(const Vector3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
        inline constexpr Vector3& operator-=(const Vector3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        inline constexpr Vector3& operator+=(const float scalar) {
            x += scalar;
            y += scalar;
            z += scalar;
            return *this;
        }
        inline constexpr Vector3& operator-=(const float scalar) {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            return *this;
        }
        inline constexpr Vector3& operator*=(const float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        inline constexpr Vector3& operator/=(const float scalar) {
            assert(scalar != 0);
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        inline constexpr Vector3 operator+(const Vector3& other) const {
            return Vector3(
                x + other.x,
                y + other.y,
                z + other.z);
        }
        inline constexpr Vector3 operator-(const Vector3& other) const {
            return Vector3(
                x - other.x,
                y - other.y,
                z - other.z);
        }

        inline constexpr Vector3 operator+(const float scalar) const {
            return Vector3(
                x + scalar,
                y + scalar,
                z + scalar);
        }
        inline constexpr Vector3 operator-(const float scalar) const {
            return Vector3(
                x - scalar,
                y - scalar,
                z - scalar);
        }
        inline constexpr Vector3 operator*(const float scalar) const {
            return Vector3(
                x * scalar,
                y * scalar,
                z * scalar);
        }
        inline constexpr Vector3 operator/(const float scalar) const {
            assert(scalar != 0);
            return Vector3(
                x / scalar,
                y / scalar,
                z / scalar);
        }

        inline friend constexpr Vector3 operator+(const float scalar, const Vector3& vec) {
            return Vector3(
                vec.x + scalar,
                vec.y + scalar,
                vec.z + scalar);
        }
        inline friend constexpr Vector3 operator-(const float scalar, const Vector3& vec) {
            return Vector3(
                vec.x - scalar,
                vec.y - scalar,
                vec.z - scalar);
        }
        inline friend constexpr Vector3 operator*(const float scalar, const Vector3& vec) {
            return Vector3(
                vec.x * scalar,
                vec.y * scalar,
                vec.z * scalar);
        }

        inline constexpr Vector3 operator-() const {
            return Vector3(-x, -y, -z);
        }
        inline friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
            os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
            return os;
        }

        inline constexpr bool operator==(const Vector3& other) const {
            return std::abs(x - other.x) < 1e-6f && std::abs(y - other.y) < 1e-6f && std::abs(z - other.z) < 1e-6f;
        }
        inline constexpr bool operator!=(const Vector3& other) const {
            return !(*this == other);
        }

        inline constexpr float length() const {
            return std::sqrt(x * x + y * y + z * z);
        }
        inline constexpr float lengthSqr() const {
            return x * x + y * y + z * z;
        }
        inline constexpr float dot(const Vector3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }
        inline constexpr float distance(const Vector3& other) const {
            return (*this - other).length();
        }
        inline constexpr float distanceSqr(const Vector3& other) const {
            return (*this - other).lengthSqr();
        }
        inline constexpr Vector3 normalize() const {
            float len = length();
            assert(len != 0);
            return Vector3(
                x / len,
                y / len,
                z / len);
        }
        inline constexpr Vector3 cross(const Vector3& other) const {
            return Vector3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
        }
};

inline constexpr Vector3 Vector3::zero = Vector3();
inline constexpr Vector3 Vector3::one = Vector3(1.0f);
inline constexpr Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
inline constexpr Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
inline constexpr Vector3 Vector3::forward = Vector3(0.0f, 0.0f, -1.0f);