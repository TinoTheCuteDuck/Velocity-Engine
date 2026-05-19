#pragma once

#include <math/matrices/mat4.hpp>
#include <math/ray.hpp>
#include <math/vector/vector3.hpp>

class Camera {
    public:
        Camera();
        void update();
        Ray screenPointToRay(Vector2 screenPos);

        Mat4 getViewMatrix();
        Vector3 getUp();
        Vector3 getRight();
        Vector3 getForward();
        Vector3 getPosition();

        float getYaw();
        float getPitch();

        float getFOV();
        float getFlySpeed();
        float getCursorSens();

        float getNearPlane();
        float getFarPlane();

    private:
        void computeVectors();

    private:
        float FOV = 70.0f;
        float flySpeed = 50.0f;
        float cursorSensitivity = 0.1f;
        float nearPlane = 0.1f;
        float farPlane = 5000.0f;

        float yaw = -90.0f;
        float pitch = -45.0f;
        Vector3 up;
        Vector3 right;
        Vector3 forward;
        Vector3 position = Vector3(0);
};