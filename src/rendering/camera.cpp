#include <rendering/camera.hpp>

#include <GLFW/glfw3.h>
#include <core/engine.hpp>
#include <core/input.hpp>

#include <math/matrices/mat4.hpp>
#include <math/ray.hpp>
#include <math/vector/vector3.hpp>
#include <math/vector/vector4.hpp>

Camera::Camera() {
    computeVectors();
}

void Camera::update() {
    if (movementBlocked)
        return;

    Input& input = Engine::get().input;
    float dt = Engine::get().time.getDt();
    float flightSpeed = flySpeed * dt;

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
        Vector2 mouseDelta = input.getMouseDelta();

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
    Vector2 windowSize = Engine::get().window.getWindowSize();
    float x = (screenPos.x / windowSize.x) * 2 - 1;
    float y = -((screenPos.y / windowSize.y) * 2 - 1);

    Vector4 clipCoords(x, y, -1.0f, 1.0f);
    Vector4 eyeCoords = Mat4::inverse(Mat4::projection(FOV, windowSize.x / windowSize.y, nearPlane, farPlane)) * clipCoords;

    Vector4 worldDir = Mat4::inverse(getViewMatrix()) * Vector4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
    Vector3 dir = Vector3(worldDir.x, worldDir.y, worldDir.z).normalize();

    return Ray(position, dir);
}

void Camera::computeVectors() {
    float yawRad = yaw * (std::numbers::pi / 180);
    float pitchRad = pitch * (std::numbers::pi / 180);
    forward = Vector3(std::cos(yawRad) * std::cos(pitchRad), std::sin(pitchRad), std::sin(yawRad) * std::cos(pitchRad));
    right = forward.cross(Vector3::up).normalize();
    up = right.cross(forward);
}

Mat4 Camera::getViewMatrix() {
    Vector4 col0(right.x, up.x, -forward.x, 0.0f);
    Vector4 col1(right.y, up.y, -forward.y, 0.0f);
    Vector4 col2(right.z, up.z, -forward.z, 0.0f);
    return Mat4(col0, col1, col2, Vector4(Vector3::zero, 1.0f)) * Mat4::translate(-position);
}

Vector3 Camera::getUp() {
    return up;
}

Vector3 Camera::getRight() {
    return right;
}

Vector3 Camera::getForward() {
    return forward;
}

Vector3 Camera::getPosition() {
    return position;
}

float Camera::getYaw() {
    return yaw;
}

float Camera::getPitch() {
    return pitch;
}

float Camera::getFOV() {
    return FOV;
}

float Camera::getFlySpeed() {
    return flySpeed;
}

float Camera::getCursorSens() {
    return cursorSensitivity;
}

float Camera::getNearPlane() {
    return nearPlane;
}

float Camera::getFarPlane() {
    return farPlane;
}