#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/acceleration.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

Gng2D::MovementSystem::MovementSystem(entt::registry& r)
    : registry(r)
{
}

void Gng2D::MovementSystem::operator()()
{
    updateVelocity();
    updatePosition();
}

void Gng2D::MovementSystem::updateVelocity()
{
    auto view = registry.view<Acceleration, Velocity>();
    for (const auto& [_, acceleration, velocity] : view.each())
    {
        const auto& max = velocity.max;

        velocity += acceleration;
        if (velocity.x > max and velocity.x > 0) velocity.x = max;
        if (velocity.y > max and velocity.y > 0) velocity.y = max;
        if (velocity.x < -max and velocity.x < 0) velocity.x = -max;
        if (velocity.y < -max and velocity.y < 0) velocity.y = -max;
    }
}

void Gng2D::MovementSystem::updatePosition()
{
    auto view = registry.view<Velocity, Position>();
    for(const auto& [_, velocity, position] : view.each())
    {
        position += velocity;

        velocity.x -= velocity.x * velocity.dragFactor;
        if (velocity.x * velocity.x < 0.01f) velocity.x = 0;
        velocity.y -= velocity.y * velocity.dragFactor;
        if (velocity.y * velocity.y < 0.01f) velocity.y = 0;
    }
}
