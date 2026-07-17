#include "rendering/camera.hpp"

#include "GLFW/glfw3.h"
#include "core/engine.hpp"
#include "core/input.hpp"
#include "math/matrices/mat4.hpp"
#include "math/ray.hpp"

Camera::Camera() {
    computeVectors();
}

void Camera::update() {
    if (movementBlocked)
        return;

    Input& input = Engine::get().input;
    const float dt = Engine::get().time.getDt();
    const float flightSpeed = flySpeed * dt;

    if (input.isKeyHeld(GLFW_KEY_W))
        position += forward * flightSpeed;
    if (input.isKeyHeld(GLFW_KEY_S))
        position -= forward * flightSpeed;
    if (input.isKeyHeld(GLFW_KEY_D))
        position += right * flightSpeed;
    if (input.isKeyHeld(GLFW_KEY_A))
        position -= right * flightSpeed;
    if (input.isKeyHeld(GLFW_KEY_SPACE))
        position += Vector3::up * flightSpeed;
    if (input.isKeyHeld(GLFW_KEY_LEFT_SHIFT))
        position -= Vector3::up * flightSpeed;

    if (input.isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        input.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (input.isButtonReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
        input.setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (input.isButtonHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
        const Vector2 mouseDelta = input.getMouseDelta();

        yaw += mouseDelta.x * cursorSensitivity;
        pitch -= mouseDelta.y * cursorSensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        computeVectors();
    }
}

Ray Camera::screenPointToRay(Vector2 screenPos) {
    const Vector2 windowSize = Engine::get().window.getWindowSize();
    const float x = (screenPos.x / windowSize.x) * 2 - 1;
    const float y = -((screenPos.y / windowSize.y) * 2 - 1);

    const Vector4 clipCoords(x, y, -1.0f, 1.0f);
    const Vector4 eyeCoords = Mat4::inverse(Mat4::projection(FOV, windowSize.x / windowSize.y, nearPlane, farPlane)) * clipCoords;

    const Vector4 worldDir = Mat4::inverse(getViewMatrix()) * Vector4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
    const Vector3 dir = Vector3(worldDir.x, worldDir.y, worldDir.z).normalize();

    return Ray(position, dir);
}

void Camera::computeVectors() {
    const float yawRad = yaw * (std::numbers::pi / 180);
    const float pitchRad = pitch * (std::numbers::pi / 180);
    forward = Vector3(std::cos(yawRad) * std::cos(pitchRad), std::sin(pitchRad), std::sin(yawRad) * std::cos(pitchRad));
    right = forward.cross(Vector3::up).normalize();
    up = right.cross(forward);
}

Mat4 Camera::getViewMatrix() const {
    return Mat4::lookAt(position, position + forward, up);
}

Vector3 Camera::getUp() const {
    return up;
}

Vector3 Camera::getRight() const {
    return right;
}

Vector3 Camera::getForward() const {
    return forward;
}

Vector3 Camera::getPosition() const {
    return position;
}

float Camera::getYaw() const {
    return yaw;
}

float Camera::getPitch() const {
    return pitch;
}

float Camera::getFOV() const {
    return FOV;
}

float Camera::getFlySpeed() const {
    return flySpeed;
}

float Camera::getCursorSens() const {
    return cursorSensitivity;
}

float Camera::getNearPlane() const {
    return nearPlane;
}

float Camera::getFarPlane() {
    return farPlane;
}