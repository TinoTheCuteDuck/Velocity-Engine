#pragma once

#include <math/mat4.hpp>
#include <math/vector3.hpp>

class Camera {
    private:
        Vector3 up;
        Vector3 right;
        Vector3 forward;
        float pitch;
        float yaw;

    public:
        Vector3 position;
        Camera(const Vector3& initialPosition);
        ~Camera();
        void update();
        void computeVectors();
        Mat4 getViewMatrix();
};