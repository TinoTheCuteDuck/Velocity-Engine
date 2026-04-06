#include <math/vector2.hpp>

constexpr Vector2::Vector2() : x(0.0f), y(0.0f) {}
constexpr Vector2::Vector2(const float xy) : x(xy), y(xy) {}
constexpr Vector2::Vector2(const float x, const float y) : x(x), y(y) {}

const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::right = Vector2(1.0f, 0.0f);

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}
Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator+=(const float scalar) {
    x += scalar;
    y += scalar;
    return *this;
}
Vector2& Vector2::operator-=(const float scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}
Vector2& Vector2::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector2& Vector2::operator/=(const float scalar) {
    assert(scalar != 0.0f);
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(
        x + other.x,
        y + other.y
    );
}
Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(
        x - other.x,
        y - other.y
    );
}

Vector2 operator+(const float scalar, const Vector2& vec) {
    return Vector2(
        vec.x + scalar,
        vec.y + scalar
    );
}
Vector2 operator-(const float scalar, const Vector2& vec) {
    return Vector2(
        vec.x - scalar,
        vec.y - scalar
    );
}
Vector2 operator*(const float scalar, const Vector2& vec) {
    return Vector2(
        vec.x * scalar,
        vec.y * scalar
    );
}
Vector2 Vector2::operator/(const float scalar) {
    assert(scalar != 0.0f);
    return Vector2(
        x / scalar,
        y / scalar
    );
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}
std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << vec.x << " " << vec.y;
    return os;
}

bool Vector2::operator==(const Vector2& other) const {
    const float EPSILON = 1e-6f;
    return 
        fabs(x - other.x) < EPSILON &&
        fabs(y - other.y) < EPSILON;
}
bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}

[[nodiscard]]float Vector2::length() const {
    return sqrt(x*x + y*y);
}
[[nodiscard]]float Vector2::lengthSqr() const {
    return x*x + y*y;
}
[[nodiscard]]float Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}
[[nodiscard]]float Vector2::distance(const Vector2& other) const {
    return (*this - other).length();
}
[[nodiscard]]float Vector2::distanceSqr(const Vector2& other) const {
    return (*this - other).lengthSqr();
}
[[nodiscard]]Vector2 Vector2::normalize() const {
    float len = length();
    if (len == 0.0f) return Vector2();
    return Vector2(
        x / len,
        y / len
    );
}