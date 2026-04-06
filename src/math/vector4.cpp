#include <math/vector4.hpp>

constexpr Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
constexpr Vector4::Vector4(const float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
constexpr Vector4::Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}

const Vector4 Vector4::zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::one = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::right = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::forward = Vector4(0.0f, 0.0f, -1.0f, 0.0f);

Vector4& Vector4::operator+=(const Vector4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}
Vector4& Vector4::operator-=(const Vector4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vector4& Vector4::operator+=(const float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
    return *this;
}
Vector4& Vector4::operator-=(const float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
    return *this;
}
Vector4& Vector4::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}
Vector4& Vector4::operator/=(const float scalar) {
    assert(scalar != 0.0f);
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(
        x + other.x,
        y + other.y,
        z + other.z,
        w + other.w
    );
}
Vector4 Vector4::operator-(const Vector4& other) const {
    return Vector4(
        x - other.x,
        y - other.y,
        z - other.z,
        w - other.w
    );
}

Vector4 operator+(const float scalar, const Vector4& vec) {
    return Vector4(
        vec.x + scalar,
        vec.y + scalar,
        vec.z + scalar,
        vec.w + scalar
    );
}
Vector4 operator-(const float scalar, const Vector4& vec) {
    return Vector4(
        vec.x - scalar,
        vec.y - scalar,
        vec.z - scalar,
        vec.w - scalar
    );
}
Vector4 operator*(const float scalar, const Vector4& vec) {
    return Vector4(
        vec.x * scalar,
        vec.y * scalar,
        vec.z * scalar,
        vec.w * scalar
    );
}
Vector4 Vector4::operator/(const float scalar) {
    assert(scalar != 0.0f);
    return Vector4(
        x / scalar,
        y / scalar,
        z / scalar,
        w / scalar
    );
}

Vector4 Vector4::operator-() const {
    return Vector4(-x, -y, -z, -w);
}
std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
    os << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
    return os;
}

bool Vector4::operator==(const Vector4& other) const {
    const float EPSILON = 1e-6f;
    return 
        fabs(x - other.x) < EPSILON &&
        fabs(y - other.y) < EPSILON &&
        fabs(z - other.z) < EPSILON &&
        fabs(w - other.w) < EPSILON;
}
bool Vector4::operator!=(const Vector4& other) const {
    return !(*this == other);
}

[[nodiscard]]float Vector4::length() const {
    return sqrt(x*x + y*y + z*z + w*w);
}
[[nodiscard]]float Vector4::lengthSqr() const {
    return x*x + y*y + z*z + w*w;
}
[[nodiscard]]float Vector4::dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}
[[nodiscard]]float Vector4::distance(const Vector4& other) const {
    return (*this - other).length();
}
[[nodiscard]]float Vector4::distanceSqr(const Vector4& other) const {
    return (*this - other).lengthSqr();
}
[[nodiscard]]Vector4 Vector4::normalize() const {
    float len = length();
    if (len == 0.0f) return Vector4();
    return Vector4(
        x / len,
        y / len,
        z / len,
        w / len
    );
}