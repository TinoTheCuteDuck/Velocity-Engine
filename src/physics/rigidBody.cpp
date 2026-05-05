#include <engine.hpp>
#include <rigidBody.hpp>

#include <assert.h>

RigidBody::RigidBody(Vector3 position)
    : position(position),
      velocity(),
      acceleration(),
      mass(10) {
}

void RigidBody::update() {
    Engine& engine = Engine::get();
    float dt = engine.time.getDt();

    Vector3 gravityVec3 = Vector3(0, gravity, 0);
    Vector3 force = gravityVec3 * mass;

    assert(mass > 0);
    acceleration = force / mass;
    velocity += acceleration * dt;
    velocity *= pow(airResistance, dt * 20.0f);
    position += velocity * dt;

    if (position.y <= 0.5) {
        position.y = 0.5;
        velocity.y = -velocity.y * 0.6f;
    }
}

void RigidBody::applyImpulse(Vector3 impulse) {
    velocity += impulse;
}

float RigidBody::getGravity() {
    return gravity;
}

float RigidBody::getAirResistance() {
    return airResistance;
}