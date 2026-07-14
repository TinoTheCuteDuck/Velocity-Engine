#include "physics/rigidBody.hpp"

#include "core/engine.hpp"
#include "rendering/sceneTypes.hpp"

#include <assert.h>

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
}

float RigidBody::getGravity() {
    return gravity;
}

float RigidBody::getAirResistance() {
    return airResistance;
}