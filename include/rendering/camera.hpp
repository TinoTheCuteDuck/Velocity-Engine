#pragma once

#include "math/vector/vector3.hpp"

class Mat4;
struct Ray;

class Camera {
  public:
    Camera();
    void update();
    Ray screenPointToRay(Vector2 screenPos);

    Mat4 getViewMatrix() const;
    Vector3 getUp() const;
    Vector3 getRight() const;
    Vector3 getForward() const;
    Vector3 getPosition() const;

    float getYaw() const;
    float getPitch() const;

    float getFOV() const;
    float getFlySpeed() const;
    float getCursorSens() const;

    float getNearPlane() const;
    float getFarPlane();

    bool movementBlocked = false;

  private:
    void computeVectors();

  private:
    float FOV = 70.0f;
    float flySpeed = 5.0f;
    float cursorSensitivity = 0.1f;
    float nearPlane = 0.1f;
    float farPlane = 5000.0f;

    float yaw = 180.0f;
    float pitch = 10.0f;
    Vector3 up;
    Vector3 right;
    Vector3 forward;
    Vector3 position = Vector3(7.5, 1, -0.45);
};