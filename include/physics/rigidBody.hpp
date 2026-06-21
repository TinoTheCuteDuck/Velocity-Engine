#pragma once

#include "math/vector/vector3.hpp"

struct Transform;

class RigidBody {
  public:
    void update(Transform& transform);

    float getGravity();
    float getAirResistance();

  public:
    float gravity = -9.81f;
    float airResistance = 0.98f;

    Vector3 velocity = Vector3();
    Vector3 acceleration = Vector3();
    float mass = 10.0f;
};