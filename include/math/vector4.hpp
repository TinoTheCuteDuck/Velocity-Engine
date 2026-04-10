#pragma once

#include <assert.h>
#include <cmath>
#include <iostream>
#include <math/vector3.hpp>

class Vector4 {
    public:
        float x, y, z, w;

        constexpr Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
        constexpr Vector4(const float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {};
        constexpr Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {};
        constexpr Vector4(const Vector3& vec, const float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {};

        static const Vector4 zero;
        static const Vector4 one;
        static const Vector4 up;
        static const Vector4 right;
        static const Vector4 forward;

        inline constexpr Vector4& operator+=(const Vector4& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }
        inline constexpr Vector4& operator-=(const Vector4& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }

        inline constexpr Vector4& operator+=(const float scalar) {
            x += scalar;
            y += scalar;
            z += scalar;
            w += scalar;
            return *this;
        }
        inline constexpr Vector4& operator-=(const float scalar) {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            w -= scalar;
            return *this;
        }
        inline constexpr Vector4& operator*=(const float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }
        inline constexpr Vector4& operator/=(const float scalar) {
            assert(scalar != 0);
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }

        inline constexpr Vector4 operator+(const Vector4& other) const {
            return Vector4(
                x + other.x,
                y + other.y,
                z + other.z,
                w + other.w);
        }
        inline constexpr Vector4 operator-(const Vector4& other) const {
            return Vector4(
                x - other.x,
                y - other.y,
                z - other.z,
                w - other.w);
        }

        inline constexpr Vector4 operator+(const float scalar) const {
            return Vector4(
                x + scalar,
                y + scalar,
                z + scalar,
                w + scalar);
        }
        inline constexpr Vector4 operator-(const float scalar) const {
            return Vector4(
                x - scalar,
                y - scalar,
                z - scalar,
                w - scalar);
        }
        inline constexpr Vector4 operator*(const float scalar) const {
            return Vector4(
                x * scalar,
                y * scalar,
                z * scalar,
                w * scalar);
        }
        inline constexpr Vector4 operator/(const float scalar) const {
            assert(scalar != 0);
            return Vector4(
                x / scalar,
                y / scalar,
                z / scalar,
                w / scalar);
        }

        inline friend constexpr Vector4 operator+(const float scalar, const Vector4& vec) {
            return Vector4(
                vec.x + scalar,
                vec.y + scalar,
                vec.z + scalar,
                vec.w + scalar);
        }
        inline friend constexpr Vector4 operator-(const float scalar, const Vector4& vec) {
            return Vector4(
                vec.x - scalar,
                vec.y - scalar,
                vec.z - scalar,
                vec.w - scalar);
        }
        inline friend constexpr Vector4 operator*(const float scalar, const Vector4& vec) {
            return Vector4(
                vec.x * scalar,
                vec.y * scalar,
                vec.z * scalar,
                vec.w * scalar);
        }

        inline constexpr Vector4 operator-() const {
            return Vector4(-x, -y, -z, -w);
        }
        inline friend std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
            os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
            return os;
        }

        inline constexpr bool operator==(const Vector4& other) const {
            return std::abs(x - other.x) < 1e-6f && std::abs(y - other.y) < 1e-6f && std::abs(z - other.z) < 1e-6f && std::abs(w - other.w) < 1e-6f;
        }
        inline constexpr bool operator!=(const Vector4& other) const {
            return !(*this == other);
        }

        inline constexpr float length() const {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }
        inline constexpr float lengthSqr() const {
            return x * x + y * y + z * z + w * w;
        }
        inline constexpr float dot(const Vector4& other) const {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }
        inline constexpr float distance(const Vector4& other) const {
            return (*this - other).length();
        }
        inline constexpr float distanceSqr(const Vector4& other) const {
            return (*this - other).lengthSqr();
        }
        inline constexpr Vector4 normalize() const {
            float len = length();
            assert(len != 0);
            return Vector4(
                x / len,
                y / len,
                z / len,
                w / len);
        }
};

inline constexpr Vector4 Vector4::zero = Vector4();
inline constexpr Vector4 Vector4::one = Vector4(1.0f);
inline constexpr Vector4 Vector4::up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
inline constexpr Vector4 Vector4::right = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
inline constexpr Vector4 Vector4::forward = Vector4(0.0f, 0.0f, -1.0f, 0.0f);