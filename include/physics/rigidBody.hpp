#pragma once

#include <vector3.hpp>

class RigidBody {
    public:
        Vector3 position;

        RigidBody(Vector3 position);
        void update();
        void applyImpulse(Vector3 impulse);

        float getGravity();
        float getAirResistance();

    private:
        float gravity = -9.81f;
        float airResistance = 0.98f;

        Vector3 velocity;
        Vector3 acceleration;
        float mass;
};