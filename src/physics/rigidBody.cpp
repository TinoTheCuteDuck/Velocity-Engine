#include <core/engine.hpp>

#include <assert.h>
#include <physics/rigidBody.hpp>

void RigidBody::update(Transform& transform) {
    Engine& engine = Engine::get();
    float dt = engine.time.getDt();

    Vector3 gravityVec3 = Vector3(0, gravity, 0);
    Vector3 force = gravityVec3 * mass;

    assert(mass > 0);
    acceleration = force / mass;
    velocity += acceleration * dt;
    velocity *= pow(airResistance, dt * 20.0f);
    transform.position += velocity * dt;

    if (transform.position.y <= 0.5) {
        transform.position.y = 0.5;
        velocity.y = -velocity.y * 0.6f;
    }
}

float RigidBody::getGravity() {
    return gravity;
}

float RigidBody::getAirResistance() {
    return airResistance;
}