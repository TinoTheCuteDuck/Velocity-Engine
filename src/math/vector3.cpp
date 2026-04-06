#include <math/vector3.hpp>

constexpr Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
constexpr Vector3::Vector3(const float xyz) : x(xyz), y(xyz), z(xyz) {}
constexpr Vector3::Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, -1.0f);

Vector3& Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}
Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator+=(const float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}
Vector3& Vector3::operator-=(const float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}
Vector3& Vector3::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}
Vector3& Vector3::operator/=(const float scalar) {
    assert(scalar != 0.0f);
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(
        x + other.x,
        y + other.y,
        z + other.z
    );
}
Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(
        x - other.x,
        y - other.y,
        z - other.z
    );
}

Vector3 operator+(const float scalar, const Vector3& vec) {
    return Vector3(
        vec.x + scalar,
        vec.y + scalar,
        vec.z + scalar
    );
}
Vector3 operator-(const float scalar, const Vector3& vec) {
    return Vector3(
        vec.x - scalar,
        vec.y - scalar,
        vec.z - scalar
    );
}
Vector3 operator*(const float scalar, const Vector3& vec) {
    return Vector3(
        vec.x * scalar,
        vec.y * scalar,
        vec.z * scalar
    );
}
Vector3 Vector3::operator/(const float scalar) {
    assert(scalar != 0.0f);
    return Vector3(
        x / scalar,
        y / scalar,
        z / scalar
    );
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}
std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << vec.x << " " << vec.y << " " << vec.z;
    return os;
}

bool Vector3::operator==(const Vector3& other) const {
    const float EPSILON = 1e-6f;
    return 
        fabs(x - other.x) < EPSILON &&
        fabs(y - other.y) < EPSILON &&
        fabs(z - other.z) < EPSILON;
}
bool Vector3::operator!=(const Vector3& other) const {
    return !(*this == other);
}

[[nodiscard]]float Vector3::length() const {
    return sqrt(x*x + y*y + z*z);
}
[[nodiscard]]float Vector3::lengthSqr() const {
    return x*x + y*y + z*z;
}
[[nodiscard]]float Vector3::dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}
[[nodiscard]]float Vector3::distance(const Vector3& other) const {
    return (*this - other).length();
}
[[nodiscard]]float Vector3::distanceSqr(const Vector3& other) const {
    return (*this - other).lengthSqr();
}
[[nodiscard]]Vector3 Vector3::normalize() const {
    float len = length();
    if (len == 0.0f) return Vector3();
    return Vector3(
        x / len,
        y / len,
        z / len
    );
}
[[nodiscard]]Vector3 Vector3::cross(const Vector3& other) const {
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}