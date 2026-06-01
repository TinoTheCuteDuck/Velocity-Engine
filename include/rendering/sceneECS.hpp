#pragma once

#include <math/matrices/mat4.hpp>
#include <math/vector/vector3.hpp>

struct Transform {
        Vector3 position;
        Vector3 scale;
        Vector3 rotation;

        Mat4 getMatrice() {
            return Mat4::translate(position) * Mat4::scale(scale);
        }
};