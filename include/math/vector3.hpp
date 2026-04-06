#pragma once

#include <iostream>
#include <cmath>
#include <assert.h>

class Vector3 {
    private:

    public:
        float x, y, z;
        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 up;
        static const Vector3 right;
        static const Vector3 forward;

        constexpr Vector3();
        constexpr Vector3(const float xyz);
        constexpr Vector3(const float x, const float y, const float z);

        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);

        Vector3& operator+=(const float scalar);
        Vector3& operator-=(const float scalar);
        Vector3& operator*=(const float scalar);
        Vector3& operator/=(const float scalar);

        [[nodiscard]]Vector3 operator+(const Vector3& other) const;
        [[nodiscard]]Vector3 operator-(const Vector3& other) const;

        friend Vector3 operator+(const float scalar, const Vector3& vec);
        friend Vector3 operator-(const float scalar, const Vector3& vec);
        friend Vector3 operator*(const float scalar, const Vector3& vec);
        Vector3 operator/(const float scalar);

        Vector3 operator-() const;
        friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);

        bool operator==(const Vector3& other) const;
        bool operator!=(const Vector3& other) const;

        float length() const;
        float lengthSqr() const;
        float dot(const Vector3& other) const;
        float distance(const Vector3& other) const;
        float distanceSqr(const Vector3& other) const;
        Vector3 normalize() const;
        Vector3 cross(const Vector3& other) const;
};