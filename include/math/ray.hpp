#pragma once

#include "math/vector/vector3.hpp"

struct Ray {
    Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {
        invDirection = Vector3(
            1.0f / direction.x,
            1.0f / direction.y,
            1.0f / direction.z);

        sign[0] = (invDirection.x < 0);
        sign[1] = (invDirection.y < 0);
        sign[2] = (invDirection.z < 0);
    }
    Vector3 origin;
    Vector3 direction;
    Vector3 invDirection;
    int sign[3]{};
};