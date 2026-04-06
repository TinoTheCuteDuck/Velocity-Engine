#pragma once

#include <iostream>
#include <cmath>
#include <assert.h>

class Vector2 {
    private:

    public:
        float x, y;

        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 up;
        static const Vector2 right;

        constexpr Vector2();
        constexpr Vector2(const float xy);
        constexpr Vector2(const float x, const float y);

        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);

        Vector2& operator+=(const float scalar);
        Vector2& operator-=(const float scalar);
        Vector2& operator*=(const float scalar);
        Vector2& operator/=(const float scalar);

        [[nodiscard]]Vector2 operator+(const Vector2& other) const;
        [[nodiscard]]Vector2 operator-(const Vector2& other) const;

        friend Vector2 operator+(const float scalar, const Vector2& vec);
        friend Vector2 operator-(const float scalar, const Vector2& vec);
        friend Vector2 operator*(const float scalar, const Vector2& vec);
        Vector2 operator/(const float scalar);

        Vector2 operator-() const;
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);

        bool operator==(const Vector2& other) const;
        bool operator!=(const Vector2& other) const;

        float length() const;
        float lengthSqr() const;
        float dot(const Vector2& other) const;
        float distance(const Vector2& other) const;
        float distanceSqr(const Vector2& other) const;
        Vector2 normalize() const;
};