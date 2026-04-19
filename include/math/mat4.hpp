#pragma once

#include <assert.h>
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector3.hpp>
#include <vector4.hpp>

class Mat4 {
    public:
        float m[16];

        constexpr Mat4() {
            for (int i = 0; i < 16; i++) {
                m[i] = 0.0f;
            }
            m[0] = 1.0f;
            m[5] = 1.0f;
            m[10] = 1.0f;
            m[15] = 1.0f;
        }
        constexpr Mat4(const float scalar) {
            for (int i = 0; i < 16; i++) {
                m[i] = 0.0f;
            }
            m[0] = scalar;
            m[5] = scalar;
            m[10] = scalar;
            m[15] = scalar;
        }
        constexpr Mat4(const float m[16]) {
            for (int i = 0; i < 16; i++) {
                this->m[i] = m[i];
            }
        }
        constexpr Mat4(const Vector4& col0, const Vector4& col1, const Vector4& col2, const Vector4& col3) {
            const Vector4 cols[4] = {col0, col1, col2, col3};
            for (int i = 0; i < 4; i++) {
                m[i * 4 + 0] = cols[i].x;
                m[i * 4 + 1] = cols[i].y;
                m[i * 4 + 2] = cols[i].z;
                m[i * 4 + 3] = cols[i].w;
            }
        }

        inline constexpr Mat4& operator+=(const Mat4& other) {
            for (int i = 0; i < 16; i++) {
                m[i] = m[i] + other.m[i];
            }
            return *this;
        }
        inline constexpr Mat4& operator-=(const Mat4& other) {
            for (int i = 0; i < 16; i++) {
                m[i] = m[i] - other.m[i];
            }
            return *this;
        }
        inline constexpr Mat4& operator*=(const Mat4& other) {
            Mat4 mat(0.0f);
            for (int col = 0; col < 4; col++) {
                for (int row = 0; row < 4; row++) {
                    for (int k = 0; k < 4; k++) {
                        mat.m[row + col * 4] += m[row + k * 4] * other.m[k + col * 4];
                    }
                }
            }
            for (int i = 0; i < 16; i++) {
                m[i] = mat.m[i];
            }

            return *this;
        }

        inline constexpr Mat4& operator*=(const float scalar) {
            for (int i = 0; i < 16; i++) {
                m[i] = m[i] * scalar;
            }
            return *this;
        }
        inline constexpr Mat4& operator/=(const float scalar) {
            assert(scalar != 0);
            for (int i = 0; i < 16; i++) {
                m[i] = m[i] / scalar;
            }
            return *this;
        }

        inline constexpr Mat4 operator+(const Mat4& other) const {
            Mat4 mat(0.0f);
            for (int i = 0; i < 16; i++) {
                mat.m[i] = m[i] + other.m[i];
            }
            return mat;
        }
        inline constexpr Mat4 operator-(const Mat4& other) const {
            Mat4 mat(0.0f);
            for (int i = 0; i < 16; i++) {
                mat.m[i] = m[i] - other.m[i];
            }
            return mat;
        }
        inline constexpr Mat4 operator*(const Mat4& other) const {
            Mat4 mat(0.0f);
            for (int col = 0; col < 4; col++) {
                for (int row = 0; row < 4; row++) {
                    for (int k = 0; k < 4; k++) {
                        mat.m[row + col * 4] += m[row + k * 4] * other.m[k + col * 4];
                    }
                }
            }
            return mat;
        }

        inline constexpr Mat4 operator*(const float scalar) const {
            Mat4 mat(0.0f);
            for (int i = 0; i < 16; i++) {
                mat.m[i] = m[i] * scalar;
            }
            return mat;
        }
        inline constexpr Mat4 operator/(const float scalar) const {
            assert(scalar != 0);
            Mat4 mat(0.0f);
            for (int i = 0; i < 16; i++) {
                mat.m[i] = m[i] / scalar;
            }
            return mat;
        }

        inline constexpr Vector4 operator*(const Vector4& other) const {
            return Vector4(
                other.x * m[0] + other.y * m[4] + other.z * m[8] + other.w * m[12],
                other.x * m[1] + other.y * m[5] + other.z * m[9] + other.w * m[13],
                other.x * m[2] + other.y * m[6] + other.z * m[10] + other.w * m[14],
                other.x * m[3] + other.y * m[7] + other.z * m[11] + other.w * m[15]);
        }

        inline friend std::ostream& operator<<(std::ostream& os, const Mat4& mat) {
            os << "(";
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    os << mat.m[col * 4 + row] << " ";
                }
                os << "\n";
            }
            os << ")";
            return os;
        }

        static constexpr Mat4 translate(const Vector3& other) {
            Mat4 mat(1.0f);
            mat.m[12] = other.x;
            mat.m[13] = other.y;
            mat.m[14] = other.z;
            return mat;
        }
        static constexpr Mat4 scale(const Vector3& scalar) {
            Mat4 mat(1.0f);
            mat.m[0] = scalar.x;
            mat.m[5] = scalar.y;
            mat.m[10] = scalar.z;
            return mat;
        }
        static constexpr Mat4 rotate(const float degrees, const Vector3& axis) {
            Mat4 mat(1.0f);
            Vector3 normA = axis.normalize();
            float angle = degrees * (std::numbers::pi / 180);

            float cos = std::cos(angle);
            float sin = std::sin(angle);
            float t = 1.0f - cos;

            mat.m[0] = cos + std::pow(normA.x, 2) * t;
            mat.m[1] = normA.x * normA.y * t - normA.z * sin;
            mat.m[2] = normA.x * normA.z * t + normA.y * sin;
            mat.m[4] = normA.y * normA.x * t + normA.z * sin;
            mat.m[5] = cos + std::pow(normA.y, 2) * t;
            mat.m[6] = normA.y * normA.z * t - normA.x * sin;
            mat.m[8] = normA.z * normA.x * t - normA.y * sin;
            mat.m[9] = normA.z * normA.y * t + normA.x * sin;
            mat.m[10] = cos + std::pow(normA.z, 2) * t;
            return mat;
        }
        static constexpr Mat4 projection(const float fov, const float aspect, const float near, const float far) {
            float rad = fov * (std::numbers::pi / 180);
            float t = near * std::tan(rad / 2);
            float r = t * aspect;

            Mat4 mat(0.0f);
            mat.m[0] = near / r;
            mat.m[5] = near / t;
            mat.m[10] = -(far + near) / (far - near);
            mat.m[11] = -1.0f;
            mat.m[14] = -2 * far * near / (far - near);
            return mat;
        }
};