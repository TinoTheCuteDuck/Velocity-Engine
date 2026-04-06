#pragma once

#include <iostream>
#include <cmath>
#include <assert.h>

class Vector4 {
    private:

    public:
        float x, y, z, w;
        static const Vector4 zero;
        static const Vector4 one;
        static const Vector4 up;
        static const Vector4 right;
        static const Vector4 forward;

        constexpr Vector4();
        constexpr Vector4(const float xyzw);
        constexpr Vector4(const float x, const float y, const float z, const float w);

        Vector4& operator+=(const Vector4& other);
        Vector4& operator-=(const Vector4& other);

        Vector4& operator+=(const float scalar);
        Vector4& operator-=(const float scalar);
        Vector4& operator*=(const float scalar);
        Vector4& operator/=(const float scalar);

        [[nodiscard]]Vector4 operator+(const Vector4& other) const;
        [[nodiscard]]Vector4 operator-(const Vector4& other) const;

        friend Vector4 operator+(const float scalar, const Vector4& vec);
        friend Vector4 operator-(const float scalar, const Vector4& vec);
        friend Vector4 operator*(const float scalar, const Vector4& vec);
        Vector4 operator/(const float scalar);

        Vector4 operator-() const;
        friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);

        bool operator==(const Vector4& other) const;
        bool operator!=(const Vector4& other) const;

        float length() const;
        float lengthSqr() const;
        float dot(const Vector4& other) const;
        float distance(const Vector4& other) const;
        float distanceSqr(const Vector4& other) const;
        Vector4 normalize() const;
};