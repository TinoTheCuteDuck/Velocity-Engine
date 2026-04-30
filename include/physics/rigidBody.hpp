#pragma once

#include <vector3.hpp>

class RigidBody {
    public:
        Vector3 position;

        RigidBody(Vector3 position);
        void update();

    private:
        Vector3 velocity;
        Vector3 acceleration;
        float mass;
};