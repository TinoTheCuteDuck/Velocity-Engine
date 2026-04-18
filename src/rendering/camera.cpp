#include "GLFW/glfw3.h"
#include "engineContext.hpp"
#include "input.hpp"
#include "vector3.hpp"
#include <math/vector4.hpp>
#include <rendering/camera.hpp>

Camera::Camera(const Vector3& initialPosition) : position(initialPosition), pitch(0), yaw(-90) {
    computeVectors();
}

Camera::~Camera() {
}

void Camera::computeVectors() {
    float yawRad = yaw * (std::numbers::pi / 180);
    float pitchRad = pitch * (std::numbers::pi / 180);
    forward = Vector3(std::cos(yawRad) * std::cos(pitchRad), std::sin(pitchRad), std::sin(yawRad) * std::cos(pitchRad));
    right = forward.cross(Vector3::up).normalize();
    up = right.cross(forward);
}

void Camera::update() {
    float flightSpeed = gEngineContext.flySpeed * gEngineContext.dt;
    if (Input::isKeyPressed(GLFW_KEY_W))
        position += forward * flightSpeed;
    if (Input::isKeyPressed(GLFW_KEY_S))
        position -= forward * flightSpeed;
    if (Input::isKeyPressed(GLFW_KEY_D))
        position += right * flightSpeed;
    if (Input::isKeyPressed(GLFW_KEY_A))
        position -= right * flightSpeed;
    if (Input::isKeyPressed(GLFW_KEY_SPACE))
        position += Vector3::up * flightSpeed;
    if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        position -= Vector3::up * flightSpeed;

    Vector2 mouseDelta = Input::getMouseDelta();
    yaw += mouseDelta.x * gEngineContext.cursorSensitivity * gEngineContext.dt;
    pitch -= mouseDelta.y * gEngineContext.cursorSensitivity * gEngineContext.dt;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    computeVectors();
    Input::setMouseDelta(Vector2());
}

Mat4 Camera::getViewMatrix() {
    Vector4 col0(right.x, up.x, -forward.x, 0.0f);
    Vector4 col1(right.y, up.y, -forward.y, 0.0f);
    Vector4 col2(right.z, up.z, -forward.z, 0.0f);
    return Mat4(col0, col1, col2, Vector4(Vector3::zero, 1.0f)) * Mat4::translate(-position);
}
