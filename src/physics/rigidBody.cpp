#include <engineState.hpp>
#include <rigidBody.hpp>

#include <assert.h>

RigidBody::RigidBody(Vector3 position)
    : position(position),
      velocity(),
      acceleration(),
      mass(10) {
}

void RigidBody::update() {
    float dt = EngineState::frame.dt;

    Vector3 gravity = Vector3(0, EngineState::enginePhysics.gravity, 0);
    Vector3 force = gravity * mass;

    assert(mass > 0);
    acceleration = force / mass;
    velocity += acceleration * dt;
    position += velocity * dt;

    if (position.y <= 0.5) {
        position.y = 0.5;
        velocity.y = -velocity.y * 0.6f;
    }
}