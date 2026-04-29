#include <GLFW/glfw3.h>
#include <camera.hpp>
#include <engineState.hpp>
#include <input.hpp>
#include <vector3.hpp>
#include <vector4.hpp>

Camera::Camera(const Vector3& initialPosition) : pitch(0), yaw(-90), position(initialPosition) {
    computeVectors();
}

void Camera::computeVectors() {
    float yawRad = yaw * (std::numbers::pi / 180);
    float pitchRad = pitch * (std::numbers::pi / 180);
    forward = Vector3(std::cos(yawRad) * std::cos(pitchRad), std::sin(pitchRad), std::sin(yawRad) * std::cos(pitchRad));
    right = forward.cross(Vector3::up).normalize();
    up = right.cross(forward);
}

void Camera::update() {
    float dt = EngineState::frame.dt;
    float flightSpeed = EngineState::settings.flySpeed * dt;

    if (Input::isKeyHeld(GLFW_KEY_W))
        position += forward * flightSpeed;
    if (Input::isKeyHeld(GLFW_KEY_S))
        position -= forward * flightSpeed;
    if (Input::isKeyHeld(GLFW_KEY_D))
        position += right * flightSpeed;
    if (Input::isKeyHeld(GLFW_KEY_A))
        position -= right * flightSpeed;
    if (Input::isKeyHeld(GLFW_KEY_SPACE))
        position += Vector3::up * flightSpeed;
    if (Input::isKeyHeld(GLFW_KEY_LEFT_SHIFT))
        position -= Vector3::up * flightSpeed;

    if (Input::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        Input::setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (Input::isButtonReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
        Input::setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (Input::isButtonHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
        Vector2 mouseDelta = Input::getMouseDelta();
        float cursorSensitivity = EngineState::settings.cursorSensitivity;

        yaw += mouseDelta.x * cursorSensitivity * dt;
        pitch -= mouseDelta.y * cursorSensitivity * dt;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        computeVectors();
    }
}

Mat4 Camera::getViewMatrix() {
    Vector4 col0(right.x, up.x, -forward.x, 0.0f);
    Vector4 col1(right.y, up.y, -forward.y, 0.0f);
    Vector4 col2(right.z, up.z, -forward.z, 0.0f);
    return Mat4(col0, col1, col2, Vector4(Vector3::zero, 1.0f)) * Mat4::translate(-position);
}
