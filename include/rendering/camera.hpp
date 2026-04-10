#pragma once

#include <math/mat4.hpp>
#include <math/vector3.hpp>

class Camera {
    private:
        Vector3 up;
        Vector3 right;
        Vector3 forward;

    public:
        Vector3 position;
        Camera(const Vector3& initialPosition);
        ~Camera();
        Mat4 getViewMatrix();
};