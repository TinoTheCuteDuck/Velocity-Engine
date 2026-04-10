#include <math/vector4.hpp>
#include <rendering/camera.hpp>

Camera::Camera(const Vector3& initialPosition) : position(initialPosition) {
    forward = Vector3::forward;
    right = forward.cross(Vector3::up).normalize();
    up = right.cross(forward);
}

Camera::~Camera() {
}

Mat4 Camera::getViewMatrix() {
    Vector4 col0(right.x, up.x, -forward.x, 0.0f);
    Vector4 col1(right.y, up.y, -forward.y, 0.0f);
    Vector4 col2(right.z, up.z, -forward.z, 0.0f);
    return Mat4(col0, col1, col2, Vector4(Vector3::zero, 1.0f)) * Mat4::translate(-position);
}